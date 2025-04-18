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
wchar_t szTitle[256]; // 使用 wchar_t 数组来存储加载的标题
HANDLE hMutex = nullptr; // 全局互斥量句柄
HINSTANCE hInstanceGlobal; // 保存 hInstance

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
static bool IsStartupEnabled();
static void SetStartup();

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
            wchar_t szStartupCancelled[256];
            LoadStringW(hInstanceGlobal, IDS_MSG_STARTUP_CANCELLED, szStartupCancelled, _countof(szStartupCancelled));
            wchar_t szStartupSuccess[256];
            LoadStringW(hInstanceGlobal, IDS_MSG_STARTUP_SUCCESS, szStartupSuccess, _countof(szStartupSuccess));
            wchar_t szStartupFailed[256];
            LoadStringW(hInstanceGlobal, IDS_MSG_STARTUP_FAILED, szStartupFailed, _countof(szStartupFailed));
            wchar_t szRegistryError[256];
            LoadStringW(hInstanceGlobal, IDS_MSG_REGISTRY_ERROR, szRegistryError, _countof(szRegistryError));
            wchar_t szInfoTitle[256];
            LoadStringW(hInstanceGlobal, IDS_INFO_TITLE, szInfoTitle, _countof(szInfoTitle));
            wchar_t szErrorTitle[256];
            LoadStringW(hInstanceGlobal, IDS_ERROR_TITLE, szErrorTitle, _countof(szErrorTitle));

            if (IsStartupEnabled())
            {
                // 如果已启用，则删除
                RegDeleteValueW(hKey, szTitle);
                MessageBoxW(nullptr, szStartupCancelled, szInfoTitle, MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                // 如果未启用，则设置
                lRes = RegSetValueExW(hKey,
                    szTitle, // 使用程序标题作为启动项的名称
                    0, REG_SZ, (BYTE*)szPath,
                    static_cast<DWORD>((wcslen(szPath) + 1) * sizeof(wchar_t)));
                if (lRes == ERROR_SUCCESS) MessageBoxW(nullptr, szStartupSuccess, szInfoTitle, MB_OK | MB_ICONINFORMATION);
                else MessageBoxW(nullptr, szStartupFailed, szErrorTitle, MB_OK | MB_ICONERROR);
            }
            RegCloseKey(hKey);
        }
        else
        {
            wchar_t szRegistryError[256];
            LoadStringW(hInstanceGlobal, IDS_MSG_REGISTRY_ERROR, szRegistryError, _countof(szRegistryError));
            wchar_t szErrorTitle[256];
            LoadStringW(hInstanceGlobal, IDS_ERROR_TITLE, szErrorTitle, _countof(szErrorTitle));
            MessageBoxW(nullptr, szRegistryError, szErrorTitle, MB_OK | MB_ICONERROR);
        }
    }
    else
    {
        wchar_t szPathError[256];
        LoadStringW(hInstanceGlobal, IDS_MSG_PATH_ERROR, szPathError, _countof(szPathError));
        wchar_t szErrorTitle[256];
        LoadStringW(hInstanceGlobal, IDS_ERROR_TITLE, szErrorTitle, _countof(szErrorTitle));
        MessageBoxW(nullptr, szPathError, szErrorTitle, MB_OK | MB_ICONERROR);
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    hInstanceGlobal = hInstance; // 保存 hInstance

    // 加载应用程序标题
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, _countof(szTitle));

    wchar_t szErrorTitle[256];
    LoadStringW(hInstance, IDS_ERROR_TITLE, szErrorTitle, _countof(szErrorTitle));
    wchar_t szInfoTitle[256];
    LoadStringW(hInstance, IDS_INFO_TITLE, szInfoTitle, _countof(szInfoTitle));
    wchar_t szWarningTitle[256];
    LoadStringW(hInstance, IDS_WARNING_TITLE, szWarningTitle, _countof(szWarningTitle));

    // 创建命名互斥量
    hMutex = CreateMutexW(nullptr, TRUE, MUTEX_NAME);
    if (hMutex == nullptr)
    {
        wchar_t szMutexFailed[256];
        LoadStringW(hInstance, IDS_MSG_MUTEX_FAILED, szMutexFailed, _countof(szMutexFailed));
        MessageBoxW(nullptr, szMutexFailed, szErrorTitle, MB_OK | MB_ICONERROR);
        return 1;
    }

    // 检查是否已有其他实例运行
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        wchar_t szAlreadyRunning[256];
        LoadStringW(hInstance, IDS_MSG_ALREADY_RUNNING, szAlreadyRunning, _countof(szAlreadyRunning));
        MessageBoxW(nullptr, szAlreadyRunning, szInfoTitle, MB_OK | MB_ICONINFORMATION);
        CloseHandle(hMutex);
        return 0; // 退出当前实例
    }

    // 初始化全局 COM 库
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED)))
    {
        wchar_t szComInitFailed[256];
        LoadStringW(hInstance, IDS_MSG_COM_INIT_FAILED, szComInitFailed, _countof(szComInitFailed));
        MessageBoxW(nullptr, szComInitFailed, szErrorTitle, MB_OK | MB_ICONERROR);
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
        wchar_t szIconLoadFailed[256];
        LoadStringW(hInstance, IDS_MSG_ICON_LOAD_FAILED, szIconLoadFailed, _countof(szIconLoadFailed));
        MessageBoxW(nullptr, szIconLoadFailed, szErrorTitle, MB_OK | MB_ICONERROR);
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
        wchar_t szDesktopViewWarn[512];
        LoadStringW(hInstance, IDS_MSG_DESKTOP_VIEW_WARN, szDesktopViewWarn, _countof(szDesktopViewWarn));
        MessageBoxW(nullptr, szDesktopViewWarn, szWarningTitle, MB_OK | MB_ICONWARNING);
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
    UpdateTrayIconAppearance(); // 首次设置托盘图标的提示文本

    // 添加托盘图标
    Shell_NotifyIconW(NIM_ADD, &nid);

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
    wcex.lpszMenuName = nullptr; // 不使用窗口菜单
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
            wchar_t szStartupTextEnable[256];
            LoadStringW(hInstanceGlobal, IDS_MENU_STARTUP_ENABLE, szStartupTextEnable, _countof(szStartupTextEnable));
            wchar_t szStartupTextDisable[256];
            LoadStringW(hInstanceGlobal, IDS_MENU_STARTUP_DISABLE, szStartupTextDisable, _countof(szStartupTextDisable));
            wchar_t szExitText[256];
            LoadStringW(hInstanceGlobal, IDS_MENU_EXIT, szExitText, _countof(szExitText));

            AppendMenuW(hMenu, MF_STRING, IDM_SET_STARTUP, IsStartupEnabled() ? szStartupTextDisable : szStartupTextEnable);
            AppendMenuW(hMenu, MF_SEPARATOR, 0, nullptr);
            AppendMenuW(hMenu, MF_STRING, IDM_EXIT, szExitText);
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
        wchar_t szErrorTitle[256];
        LoadStringW(hInstanceGlobal, IDS_ERROR_TITLE, szErrorTitle, _countof(szErrorTitle));
        wchar_t szControlDesktopError[256];
        LoadStringW(hInstanceGlobal, IDS_MSG_CONTROL_DESKTOP_ERROR, szControlDesktopError, _countof(szControlDesktopError));
        MessageBoxW(nullptr, szControlDesktopError, szErrorTitle, MB_OK | MB_ICONERROR);
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
        wchar_t szTipHide[256];
        LoadStringW(hInstanceGlobal, IDS_TRAY_TIP_HIDE, szTipHide, _countof(szTipHide));
        wchar_t szTipShow[256];
        LoadStringW(hInstanceGlobal, IDS_TRAY_TIP_SHOW, szTipShow, _countof(szTipShow));
        nid.hIcon = desktopIconsVisible ? hIconVisible : hIconHidden;
        wcscpy_s(nid.szTip, _countof(nid.szTip), desktopIconsVisible ? szTipHide : szTipShow);
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