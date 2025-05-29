#pragma region We will now review the implementation

#include <QtGui>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h" // We will implement it in Chapter 4.

MainWindow::MainWindow() {
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);
    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    readSettings();
    findDialog = 0;
    setWindowIcon(QIcon(":/images/icon.png")); //MINE: See the comment below.
    setCurrentFile("");
}
#pragma endregion //We will now review the implementation

/* Perplexity

Is the .pro-file available with CMake Qt projects? How to access it in Qt 6.9?
To make use of Qt's resource system, we must create a resource file and add a line to the .pro file that identifies the resource
file. In this example, we have called the resource file spreadsheet.qrc, so we put the following line in the .pro file:
RESOURCES = spreadsheet.qrc
The resource file itself uses a simple XML format. Here's an extract from the one we have used:
images/icon.png
...
images/gotocell.png
The .pro file is specific to the qmake build system and is not used or available in CMake-based Qt projects, including those using Qt 6.9. Qt 6 and later strongly encourage using CMake as the primary build system instead of qmake, and the .pro file is replaced by CMakeLists.txt files for project configuration and building[1][2].
Accessing and Using Qt Resources in Qt 6.9 with CMake
In qmake projects, you specify resource files in the .pro file with a line like:
RESOURCES = spreadsheet.qrc

and the resource compiler (rcc) processes the .qrc files accordingly[3].
In CMake-based Qt projects (Qt 6.9), you do not use .pro files. Instead, you integrate Qt resources using CMake commands. The recommended way is to use the qt_add_resources() function provided by Qt's CMake integration. For example:
qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})

This tells CMake to process the .qrc file and generate the necessary code to embed the resources into your application. Also, ensure CMAKE_AUTORCC is enabled (which is usually on by default in Qt projects) so that resource files are automatically processed[4][3].
Summary
•	The .pro file is not available or used in CMake-based Qt projects, including Qt 6.9[1][2].
•	To use Qt resource files (.qrc) in Qt 6.9 with CMake, use qt_add_resources() in your CMakeLists.txt to add resource files to your target[4][3].
•	The resource system remains the same conceptually but is integrated differently depending on the build system (qmake vs CMake)[3].
Thus, if you are migrating from a .pro-based Qt project to CMake in Qt 6.9, you should convert your .pro resource declarations into appropriate qt_add_resources() calls in your CMake configuration.
⁂

<q>qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})</q> Where must spreadsheet.qrc be located?
Great question! When using qt_add_resources() in your CMakeLists.txt like this:
qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})

Where Should spreadsheet.qrc Be Located?
•	Relative to the CMakeLists.txt file:
The path to spreadsheet.qrc is interpreted relative to the directory containing the CMakeLists.txt file where qt_add_resources() is called.
•	Example:
If your project structure is:
MyProject/
├── CMakeLists.txt
├── spreadsheet.qrc
└── main.cpp

Then simply specifying spreadsheet.qrc works fine.
•	If located in a subdirectory:
If your resource file is inside a folder, for example resources/spreadsheet.qrc, you should specify the relative path accordingly:
qt_add_resources(RES_SOURCES resources/spreadsheet.qrc)

Important Notes:
•	The .qrc file path must be accessible at configure time by CMake.
•	You can also use absolute paths, but relative paths are recommended for portability.
•	If you move your CMakeLists.txt into a subdirectory, adjust the path to the .qrc file accordingly.

Summary
Location of spreadsheet.qrc	How to specify in qt_add_resources()
Same directory as CMakeLists.txt	spreadsheet.qrc
In a subfolder resources/	resources/spreadsheet.qrc
Elsewhere (not recommended)	Use relative or absolute path accordingly


If you want, I can help you with example project structures or more detailed CMake setup!

 Yes.
Here's an example of a well-structured Qt 6.9 project using CMake that includes a resource file (spreadsheet.qrc), showing where to place files and how to set up your CMakeLists.txt files:

Example Project Structure
MyQtProject/
├── CMakeLists.txt           # Top-level CMake file
├── resources/
│   └── spreadsheet.qrc      # Qt resource file here
├── src/
│   ├── main.cpp             # Main application source
│   ├── mainwindow.cpp       # Implementation of main window
│   ├── mainwindow.h         # Header for main window
│   ├── mainwindow.ui        # UI file (optional)
│   └── CMakeLists.txt       # CMake file for the app target


Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(MyQtProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 Widgets module (adjust components as needed)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Setup project with Qt standard settings
qt_standard_project_setup()

# Add the subdirectory containing the app sources
add_subdirectory(src)


src/CMakeLists.txt
# Add Qt resource file relative to this CMakeLists.txt
qt_add_resources(RES_SOURCES ../resources/spreadsheet.qrc)

# Add executable target with sources and generated resource sources
qt_add_executable(MyApp
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    ${RES_SOURCES}
)

# Link Qt libraries
target_link_libraries(MyApp PRIVATE Qt6::Widgets)

# Optional: set properties for platform-specific bundles
set_target_properties(MyApp PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)


Explanation
•	The .qrc file is located in the resources/ folder at the project root.
•	In src/CMakeLists.txt, the path to the resource file is given relative to that CMakeLists.txt, hence ../resources/spreadsheet.qrc.
•	The qt_add_resources() macro processes the .qrc file and generates source files that are included in the target.
•	The qt_add_executable() command declares the executable and includes UI files, source files, and resource-generated sources.
•	The top-level CMakeLists.txt handles overall project setup and calls add_subdirectory(src) to build the app target.

This structure cleanly separates resources, sources, and build configuration, making it easy to maintain and extend your Qt project with CMake in Qt 6.9
*/
