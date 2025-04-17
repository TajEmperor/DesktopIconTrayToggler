#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include "resource.h"

// --- 定义 ---
#define WM_TRAYICON (WM_USER + 1)
#define REGISTRY_KEY L"Software\\DesktopIconToggler"
#define REGISTRY_VALUE L"DesktopIconsVisible"
#define MUTEX_NAME L"DesktopIconTogglerMutex" // 定义互斥量名称

// --- 全局变量 ---
NOTIFYICONDATA nid;
HICON hIconVisible = nullptr;
HICON hIconHidden = nullptr;
bool desktopIconsVisible = true;
HWND desktopListViewHandle = nullptr;
HWND hWndMain = nullptr; // 主窗口句柄，不显示但需要
const wchar_t szWindowClass[] = L"TrayAppContextClass";
const wchar_t szTitle[] = L"Desktop Icon Toggler";
HANDLE hMutex = nullptr; // 全局互斥量句柄

// --- 函数声明 ---
HWND GetDesktopListViewHandle();
void UpdateTrayIconAppearance();
void ToggleDesktopIcons();
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool InitInstance(HINSTANCE hInstance, int nCmdShow);
ATOM MyRegisterClass(HINSTANCE hInstance);
void Cleanup();
bool LoadDesktopIconsState();
void SaveDesktopIconsState();

// 用于 EnumWindows 的回调函数
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    HWND shellDefView = FindWindowExW(hWnd, nullptr, L"SHELLDLL_DefView", nullptr);
    if (shellDefView) {
        *(HWND*)lParam = hWnd;
        return FALSE; // 停止枚举
    }
    return TRUE;
}

static bool IsStartupEnabled()
{
    HKEY hKey;
    LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
        0, KEY_READ, &hKey);

    if (lRes == ERROR_SUCCESS)
    {
        wchar_t szPath[MAX_PATH];
        DWORD dwSize = sizeof(szPath);
        DWORD dwType = REG_SZ;

        lRes = RegQueryValueExW(hKey,
            szTitle, // 使用程序标题作为启动项的名称
            nullptr, &dwType, (BYTE*)szPath, &dwSize);

        RegCloseKey(hKey);

        if (lRes == ERROR_SUCCESS)
        {
            wchar_t currentPath[MAX_PATH];
            if (GetModuleFileNameW(nullptr, currentPath, MAX_PATH)) return _wcsicmp(currentPath, szPath) == 0; // 比较路径是否一致
        }
    }
    return false;
}

static void SetStartup()
{
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileNameW(nullptr, szPath, MAX_PATH))
    {
        HKEY hKey;
        LONG lRes = RegOpenKeyExW(HKEY_CURRENT_USER,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
            0, KEY_WRITE, &hKey);

        if (lRes == ERROR_SUCCESS)
        {
            if (IsStartupEnabled())
            {
                // 如果已启用，则删除
                RegDeleteValueW(hKey, szTitle);
                MessageBoxW(nullptr, L"已取消开机启动。", L"提示", MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                // 如果未启用，则设置
                lRes = RegSetValueExW(hKey,
                    szTitle, // 使用程序标题作为启动项的名称
                    0, REG_SZ, (BYTE*)szPath,
                    static_cast<DWORD>((wcslen(szPath) + 1) * sizeof(wchar_t)));
                if (lRes == ERROR_SUCCESS) MessageBoxW(nullptr, L"已成功设置为开机启动。", L"提示", MB_OK | MB_ICONINFORMATION);
                else MessageBoxW(nullptr, L"设置开机启动失败。", L"错误", MB_OK | MB_ICONERROR);
            }
            RegCloseKey(hKey);
        }
        else MessageBoxW(nullptr, L"无法访问注册表。", L"错误", MB_OK | MB_ICONERROR);
    }
    else MessageBoxW(nullptr, L"无法获取程序路径。", L"错误", MB_OK | MB_ICONERROR);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 创建命名互斥量
    hMutex = CreateMutexW(nullptr, TRUE, MUTEX_NAME);
    if (hMutex == nullptr)
    {
        MessageBoxW(nullptr, L"创建互斥量失败！", L"错误", MB_OK | MB_ICONERROR);
        return 1;
    }

    // 检查是否已有其他实例运行
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        MessageBoxW(nullptr, L"程序已经在运行！", L"提示", MB_OK | MB_ICONINFORMATION);
        CloseHandle(hMutex);
        return 0; // 退出当前实例
    }

    // 初始化全局 COM 库
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
    {
        MessageBoxW(nullptr, L"无法初始化 COM 库。", L"错误", MB_OK | MB_ICONERROR);
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return 1;
    }

    MyRegisterClass(hInstance);

    // 执行应用程序初始化
    if (!InitInstance(hInstance, nCmdShow))
    {
        CoUninitialize();
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return 1;
    }

    // 加载内嵌图标
    hIconVisible = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_VISIBLE));
    hIconHidden = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_HIDDEN));

    if (!hIconVisible || !hIconHidden) {
        MessageBoxW(nullptr, L"加载内嵌图标失败。", L"错误", MB_OK | MB_ICONERROR);
        Cleanup();
        CoUninitialize();
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        return 1;
    }

    // 加载上次的桌面图标状态
    if (!LoadDesktopIconsState()) {
        // 如果加载失败，默认显示图标
        desktopIconsVisible = true;
    }

    // 获取桌面图标列表视图的句柄
    desktopListViewHandle = GetDesktopListViewHandle();
    if (!desktopListViewHandle) {
        MessageBoxW(nullptr, L"未能找到桌面图标列表视图。\n此功能可能无法在此版本的 Windows 或特定配置下工作。", L"警告", MB_OK | MB_ICONWARNING);
        // 程序仍然可以运行（仅托盘图标）
    }
    else {
        // 根据加载的状态设置桌面图标的可见性
        ShowWindow(desktopListViewHandle, desktopIconsVisible ? SW_SHOW : SW_HIDE);
    }

    // 初始化托盘图标数据
    memset(&nid, 0, sizeof(nid));
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hWndMain;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.hIcon = hIconVisible;
    nid.uCallbackMessage = WM_TRAYICON;
    wcscpy_s(nid.szTip, _countof(nid.szTip), desktopIconsVisible ? L"单击以隐藏桌面图标" : L"单击以显示桌面图标");

    // 添加托盘图标
    Shell_NotifyIconW(NIM_ADD, &nid);

    // 根据加载的状态更新托盘图标
    UpdateTrayIconAppearance();

    // 主消息循环
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Cleanup();
    CoUninitialize();
    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
    return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_DESKTOPICONTRAYTOGGLER));
    wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIconW(wcex.hInstance, MAKEINTRESOURCEW(IDI_DESKTOPICONTRAYTOGGLER));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们将实例句柄保存在全局变量中并创建
//        主程序窗口。
//
bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    hWndMain = hWnd; // 保存主窗口句柄

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_TRAYICON:
        if (lParam == WM_LBUTTONDOWN) {
            ToggleDesktopIcons();
        }
        else if (lParam == WM_RBUTTONDOWN) {
            POINT pt;
            GetCursorPos(&pt);
            HMENU hMenu = CreatePopupMenu();
            AppendMenuW(hMenu, MF_STRING, IDM_SET_STARTUP, IsStartupEnabled() ? L"取消开机启动(&D)" : L"设为开机启动(&S)");
            AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
            AppendMenuW(hMenu, MF_STRING, IDM_EXIT, L"退出(&X)");
            SetForegroundWindow(hWnd); // 确保菜单在鼠标位置正确显示
            TrackPopupMenu(hMenu, TPM_LEFTALIGN, pt.x, pt.y, 0, hWnd, nullptr);
            DestroyMenu(hMenu);
        }
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_SET_STARTUP:
            // 处理“设为开机启动”
            SetStartup();
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        // 保存当前的桌面图标状态
        SaveDesktopIconsState();
        Shell_NotifyIconW(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

HWND GetDesktopListViewHandle()
{
    HWND progman = FindWindowW(L"Progman", nullptr);
    if (!progman) return nullptr;

    HWND shellDefView = FindWindowExW(progman, nullptr, L"SHELLDLL_DefView", nullptr);
    if (!shellDefView)
    {
        HWND workerW = nullptr;
        EnumWindows(EnumWindowsProc, (LPARAM)&workerW);
        if (workerW) shellDefView = FindWindowExW(workerW, nullptr, L"SHELLDLL_DefView", nullptr);
        if (!shellDefView) return nullptr;
    }

    HWND listView = FindWindowExW(shellDefView, nullptr, L"SysListView32", L"FolderView");
    if (!listView) listView = FindWindowExW(shellDefView, nullptr, L"SysListView32", nullptr);

    return listView;
}

void ToggleDesktopIcons()
{
    if (!desktopListViewHandle) {
        MessageBoxW(nullptr, L"无法控制桌面图标，因为未能找到其窗口句柄。", L"错误", MB_OK | MB_ICONERROR);
        return;
    }

    desktopIconsVisible = !desktopIconsVisible;
    ShowWindow(desktopListViewHandle, desktopIconsVisible ? SW_SHOW : SW_HIDE);
    UpdateTrayIconAppearance();
}

void UpdateTrayIconAppearance()
{
    if (hIconVisible && hIconHidden)
    {
        nid.hIcon = desktopIconsVisible ? hIconVisible : hIconHidden;
        wcscpy_s(nid.szTip, _countof(nid.szTip), desktopIconsVisible ? L"单击以隐藏桌面图标" : L"单击以显示桌面图标");
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
}

void Cleanup()
{
    if (hIconVisible) DestroyIcon(hIconVisible);
    if (hIconHidden) DestroyIcon(hIconHidden);
    Shell_NotifyIconW(NIM_DELETE, &nid);
    if (hMutex)
    {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        hMutex = nullptr;
    }
}

bool LoadDesktopIconsState()
{
    HKEY hKey;
    DWORD dwValue;
    DWORD dwType = REG_DWORD;
    DWORD dwSize = sizeof(dwValue);

    if (RegOpenKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueExW(hKey, REGISTRY_VALUE, nullptr, &dwType, (LPBYTE)&dwValue, &dwSize) == ERROR_SUCCESS)
        {
            desktopIconsVisible = (dwValue != 0);
            RegCloseKey(hKey);
            return true;
        }
        RegCloseKey(hKey);
    }
    return false; // 无法加载，返回 false
}

void SaveDesktopIconsState()
{
    HKEY hKey;
    DWORD dwValue = desktopIconsVisible ? 1 : 0;

    if (RegCreateKeyExW(HKEY_CURRENT_USER, REGISTRY_KEY, 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_WRITE, nullptr, &hKey, nullptr) == ERROR_SUCCESS)
    {
        RegSetValueExW(hKey, REGISTRY_VALUE, 0, REG_DWORD, (const BYTE*)&dwValue, sizeof(dwValue));
        RegCloseKey(hKey);
    }
}