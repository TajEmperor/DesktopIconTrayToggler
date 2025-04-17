# DesktopIconTrayToggler

[![License](https://img.shields.io/badge/License-WTFPL-yellow.svg)](https://www.wtfpl.net/)

**English** | [中文](#中文)

## Description

DesktopIconTrayToggler is a lightweight Windows application that resides in the system tray and allows you to toggle the visibility of your desktop icons with a single click. It provides a convenient and quick way to declutter your desktop when needed and bring back your icons instantly.

## Features

* **Toggle Desktop Icons:** Easily show or hide your desktop icons with a single click on the system tray icon.
* **System Tray Application:** Runs in the background and can be accessed from the system tray.
* **Startup Management:** Option to enable or disable the application from starting automatically when you log in.
* **Persistent State:** Remembers whether your desktop icons were visible or hidden in the previous session.
* **Single Instance:** Ensures only one instance of the application is running at a time.

## Getting Started

### Prerequisites

* A Windows operating system.

### Usage

1.  **Download:** Download the compiled executable (`.exe` file) from the [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases) page.
2.  **Run:** Double-click the executable file to run the application.
3.  **System Tray:** The application will appear as an icon in your system tray.
4.  **Toggle Icons:**
    * **Left-click** the tray icon to toggle the visibility of your desktop icons.
    * **Right-click** the tray icon to open a menu with options to manage startup and exit the application.

## Building the Application

### Prerequisites

* [Visual Studio](https://visualstudio.microsoft.com/) (with C++ workload installed).

### Steps

1.  **Clone the Repository:**
    ```bash
    git clone https://github.com/racpast/DesktopIconTrayToggler.git
    cd DesktopIconTrayToggler
    ```
2.  **Open in Visual Studio:** Open the `DesktopIconTrayToggler.sln` file in Visual Studio.
3.  **Build:** Build the solution (e.g., by going to `Build` > `Build Solution`).
4.  **Executable:** The compiled executable (`.exe` file) will be located in the `Debug` or `Release` folder, depending on your build configuration.

## License

This project is licensed under the WTFPL License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

* This project utilizes standard Windows API functions.

---

<a name="中文"></a>

**中文**

## 描述

DesktopIconTrayToggler 是一个轻量级的 Windows 应用程序，它驻留在系统托盘中，让您只需单击一下即可切换桌面图标的可见性。它提供了一种方便快捷的方式，在需要时整理您的桌面，并立即恢复您的图标。

## 功能特性

* **切换桌面图标:** 通过单击系统托盘图标，轻松显示或隐藏您的桌面图标。
* **系统托盘应用:** 在后台运行，并可以通过系统托盘进行访问。
* **启动管理:** 可选择启用或禁用应用程序在您登录时自动启动。
* **状态持久化:** 记住上次会话中桌面图标是显示还是隐藏的状态。
* **单实例:** 确保一次只运行一个应用程序实例。

## 开始使用

### 前置条件

* Windows 操作系统。

### 使用方法

1.  **下载:** 从 [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases) 页面下载已编译的可执行文件 (`.exe` 文件) 。
2.  **运行:** 双击可执行文件以运行应用程序。
3.  **系统托盘:** 应用程序将显示在您的系统托盘中。
4.  **切换图标:**
    * **左键单击**托盘图标以切换桌面图标的可见性。
    * **右键单击**托盘图标以打开一个菜单，其中包含管理启动和退出应用程序的选项。

## 构建应用程序

### 前置条件

* [Visual Studio](https://visualstudio.microsoft.com/) (需要安装 C++ 工作负载)。

### 步骤

1.  **克隆仓库:**
    ```bash
    git clone https://github.com/racpast/DesktopIconTrayToggler.git
    cd DesktopIconTrayToggler
    ```
    (将 `YOUR_GITHUB_USERNAME` 替换为您的实际用户名。)
2.  **在 Visual Studio 中打开:** 在 Visual Studio 中打开 `DesktopIconTrayToggler.sln` 文件。
3.  **构建:** 构建解决方案 (例如，转到 `生成` > `生成解决方案`)。
4.  **可执行文件:** 编译后的可执行文件 (`.exe` 文件) 将位于 `Debug` 或 `Release` 文件夹中，具体取决于您的构建配置。

## 许可证

本项目采用 WTFPL 许可证 - 有关详细信息，请参阅 [LICENSE](LICENSE) 文件。

## 致谢

* 本项目使用了标准的 Windows API 函数。
