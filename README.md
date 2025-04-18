# DesktopIconTrayToggler

[![License](https://img.shields.io/badge/License-WTFPL-yellow.svg)](https://www.wtfpl.net/)

**English** | [中文](#中文) | [日本語](#日本語) | [Français](#Français) | [Deutsch](#Deutsch) | [繁體中文](#繁體中文)

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
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
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
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
    cd DesktopIconTrayToggler
    ```
2.  **在 Visual Studio 中打开:** 在 Visual Studio 中打开 `DesktopIconTrayToggler.sln` 文件。
3.  **构建:** 构建解决方案 (例如，转到 `生成` > `生成解决方案`)。
4.  **可执行文件:** 编译后的可执行文件 (`.exe` 文件) 将位于 `Debug` 或 `Release` 文件夹中，具体取决于您的构建配置。

## 许可证

本项目采用 WTFPL 许可证 - 有关详细信息，请参阅 [LICENSE](LICENSE) 文件。

## 致谢

* 本项目使用了标准的 Windows API 函数。

---

<a name="日本語"></a>

**日本語**

## 概要 (Description)

DesktopIconTrayToggler は、システムトレイに常駐し、ワンクリックでデスクトップアイコンの表示/非表示を切り替えられる軽量な Windows アプリケーションです。必要に応じてデスクトップをすばやく整理し、アイコンを即座に戻す便利な方法を提供します。

## 機能 (Features)

* **デスクトップアイコンの切り替え:** システムトレイアイコンをワンクリックするだけで、デスクトップアイコンの表示/非表示を簡単に切り替えます。
* **システムトレイアプリケーション:** バックグラウンドで実行され、システムトレイからアクセスできます。
* **スタートアップ管理:** ログイン時にアプリケーションを自動的に起動するかどうかを有効または無効にするオプションがあります。
* **状態の永続化:** 前回のセッションでデスクトップアイコンが表示されていたか非表示だったかを記憶します。
* **シングルインスタンス:** アプリケーションの単一のインスタンスのみが一度に実行されるようにします。

## はじめに (Getting Started)

### 前提条件 (Prerequisites)

* Windows オペレーティングシステム。

### 使用方法 (Usage)

1.  **ダウンロード:** [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases) ページからコンパイル済み実行可能ファイル (`.exe` ファイル) をダウンロードします。
2.  **実行:** 実行可能ファイルをダブルクリックしてアプリケーションを実行します。
3.  **システムトレイ:** アプリケーションはシステムトレイにアイコンとして表示されます。
4.  **アイコンの切り替え:**
    * トレイアイコンを**左クリック**すると、デスクトップアイコンの表示/非表示が切り替わります。
    * トレイアイコンを**右クリック**すると、スタートアップ管理やアプリケーションを終了するオプションを含むメニューが開きます。

## アプリケーションのビルド (Building the Application)

### 前提条件 (Prerequisites)

* [Visual Studio](https://visualstudio.microsoft.com/) (C++ ワークロードがインストールされている必要があります)。

### 手順 (Steps)

1.  **リポジトリのクローン:**
    ```bash
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
    cd DesktopIconTrayToggler
    ```
2.  **Visual Studio で開く:** `DesktopIconTrayToggler.sln` ファイルを Visual Studio で開きます。
3.  **ビルド:** ソリューションをビルドします (例: `ビルド` > `ソリューションのビルド` を選択)。
4.  **実行可能ファイル:** コンパイルされた実行可能ファイル (`.exe` ファイル) は、ビルド構成に応じて `Debug` または `Release` フォルダにあります。

## ライセンス (License)

このプロジェクトは WTFPL ライセンスの下でライセンスされています - 詳細については [LICENSE](LICENSE) ファイルを参照してください。

## 謝辞 (Acknowledgements)

* このプロジェクトは標準的な Windows API 関数を利用しています。

---

<a name="Français"></a>

**Français**

## Description

DesktopIconTrayToggler est une application Windows légère qui réside dans la barre d'état système et vous permet de basculer la visibilité de vos icônes de bureau en un seul clic. Elle offre un moyen pratique et rapide de désencombrer votre bureau en cas de besoin et de ramener instantanément vos icônes.

## Fonctionnalités

* **Basculer les icônes du bureau :** Affichez ou masquez facilement vos icônes de bureau en un seul clic sur l'icône de la barre d'état système.
* **Application de la barre d'état système :** S'exécute en arrière-plan et est accessible depuis la barre d'état système.
* **Gestion du démarrage :** Option pour activer ou désactiver le démarrage automatique de l'application lorsque vous vous connectez.
* **État persistant :** Se souvient si vos icônes de bureau étaient visibles ou masquées lors de la session précédente.
* **Instance unique :** Garantit qu'une seule instance de l'application est en cours d'exécution à la fois.

## Pour commencer

### Prérequis

* Un système d'exploitation Windows.

### Utilisation

1.  **Télécharger :** Téléchargez l'exécutable compilé (fichier `.exe`) depuis la page [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases).
2.  **Exécuter :** Double-cliquez sur le fichier exécutable pour exécuter l'application.
3.  **Barre d'état système :** L'application apparaîtra sous la forme d'une icône dans votre barre d'état système.
4.  **Basculer les icônes :**
    * **Cliquez avec le bouton gauche** sur l'icône de la barre d'état système pour basculer la visibilité de vos icônes de bureau.
    * **Cliquez avec le bouton droit** sur l'icône de la barre d'état système pour ouvrir un menu avec des options de gestion du démarrage et de sortie de l'application.

## Construction de l'application

### Prérequis

* [Visual Studio](https://visualstudio.microsoft.com/) (avec la charge de travail C++ installée).

### Étapes

1.  **Cloner le dépôt :**
    ```bash
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
    cd DesktopIconTrayToggler
    ```
2.  **Ouvrir dans Visual Studio :** Ouvrez le fichier `DesktopIconTrayToggler.sln` dans Visual Studio.
3.  **Construire :** Construisez la solution (par exemple, en allant dans `Build` > `Build Solution`).
4.  **Exécutable :** L'exécutable compilé (fichier `.exe`) se trouvera dans le dossier `Debug` ou `Release`, en fonction de votre configuration de build.

## Licence

Ce projet est sous licence WTFPL - consultez le fichier [LICENSE](LICENSE) pour plus de détails.

## Remerciements

* Ce projet utilise les fonctions API standard de Windows.

---

<a name="Deutsch"></a>

**Deutsch**

## Beschreibung

DesktopIconTrayToggler ist eine leichte Windows-Anwendung, die sich im System-Tray befindet und Ihnen ermöglicht, die Sichtbarkeit Ihrer Desktop-Symbole mit einem einzigen Klick umzuschalten. Es bietet eine bequeme und schnelle Möglichkeit, Ihren Desktop bei Bedarf aufzuräumen und Ihre Symbole sofort wiederherzustellen.

## Funktionen

* **Desktop-Symbole umschalten:** Zeigen oder verstecken Sie Ihre Desktop-Symbole einfach mit einem einzigen Klick auf das System-Tray-Symbol.
* **System-Tray-Anwendung:** Läuft im Hintergrund und ist über das System-Tray zugänglich.
* **Startverwaltung:** Option zum Aktivieren oder Deaktivieren des automatischen Starts der Anwendung beim Einloggen.
* **Permanenter Status:** Speichert, ob Ihre Desktop-Symbole in der vorherigen Sitzung sichtbar oder ausgeblendet waren.
* **Einzelinstanz:** Stellt sicher, dass nur eine Instanz der Anwendung gleichzeitig ausgeführt wird.

## Erste Schritte

### Voraussetzungen

* Ein Windows-Betriebssystem.

### Verwendung

1.  **Herunterladen:** Laden Sie die kompilierte ausführbare Datei (`.exe` Datei) von der [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases) Seite herunter.
2.  **Ausführen:** Doppelklicken Sie auf die ausführbare Datei, um die Anwendung auszuführen.
3.  **System-Tray:** Die Anwendung wird als Symbol in Ihrem System-Tray angezeigt.
4.  **Symbole umschalten:**
    * **Klicken Sie mit der linken Maustaste** auf das Tray-Symbol, um die Sichtbarkeit Ihrer Desktop-Symbole umzuschalten.
    * **Klicken Sie mit der rechten Maustaste** auf das Tray-Symbol, um ein Menü mit Optionen zur Startverwaltung und zum Beenden der Anwendung zu öffnen.

## Erstellen der Anwendung

### Voraussetzungen

* [Visual Studio](https://visualstudio.microsoft.com/) (mit installierter C++-Workload).

### Schritte

1.  **Das Repository klonen:**
    ```bash
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
    cd DesktopIconTrayToggler
    ```
2.  **In Visual Studio öffnen:** Öffnen Sie die Datei `DesktopIconTrayToggler.sln` in Visual Studio.
3.  **Erstellen:** Erstellen Sie die Projektmappe (z. B. über `Build` > `Build Solution`).
4.  **Ausführbare Datei:** Die kompilierte ausführbare Datei (`.exe` Datei) befindet sich je nach Ihrer Build-Konfiguration im `Debug`- oder `Release`-Ordner.

## Lizenz

Dieses Projekt ist unter der WTFPL-Lizenz lizenziert - siehe die Datei [LICENSE](LICENSE) für Details.

## Danksagungen

* Dieses Projekt verwendet standardmäßige Windows API-Funktionen.

---

<a name="繁體中文"></a>

**繁體中文**

## 描述

DesktopIconTrayToggler 是一個輕量級的 Windows 應用程式，它駐留在系統匣中，讓您只需點擊一下即可切換桌面圖示的可見性。它提供了一種方便快捷的方式，在需要時整理您的桌面，並立即恢復您的圖示。

## 功能特性

* **切換桌面圖示:** 透過點擊系統匣圖示，輕鬆顯示或隱藏您的桌面圖示。
* **系統匣應用程式:** 在背景執行，並可以透過系統匣進行存取。
* **啟動管理:** 可選擇啟用或停用應用程式在您登入時自動啟動。
* **狀態持久化:** 記住上次會話中桌面圖示是顯示還是隱藏的狀態。
* **單一實例:** 確保一次只執行一個應用程式實例。

## 開始使用

### 前置條件

* Windows 作業系統。

### 使用方法

1.  **下載:** 從 [Releases](https://github.com/racpast/DesktopIconTrayToggler/releases) 頁面下載已編譯的可執行檔 (`.exe` 檔案)。
2.  **執行:** 雙擊可執行檔以執行應用程式。
3.  **系統匣:** 應用程式將顯示在您的系統匣中。
4.  **切換圖示:**
    * **左鍵點擊**系統匣圖示以切換桌面圖示的可見性。
    * **右鍵點擊**系統匣圖示以開啟一個選單，其中包含管理啟動和退出應用程式的選項。

## 建置應用程式

### 前置條件

* [Visual Studio](https://visualstudio.microsoft.com/) (需要安裝 C++ 工作負載)。

### 步驟

1.  **複製儲存庫:**
    ```bash
    git clone [https://github.com/racpast/DesktopIconTrayToggler.git](https://github.com/racpast/DesktopIconTrayToggler.git)
    cd DesktopIconTrayToggler
    ```
2.  **在 Visual Studio 中開啟:** 在 Visual Studio 中開啟 `DesktopIconTrayToggler.sln` 檔案。
3.  **建置:** 建置解決方案 (例如，前往 `建置` > `建置解決方案`)。
4.  **可執行檔:** 編譯後的可執行檔 (`.exe` 檔案) 將位於 `Debug` 或 `Release` 資料夾中，具體取決於您的建置組態。

## 授權

本專案採用 WTFPL 授權 - 有關詳細資訊，請參閱 [LICENSE](LICENSE) 檔案。

## 致謝

* 本專案使用了標準的 Windows API 函數。
