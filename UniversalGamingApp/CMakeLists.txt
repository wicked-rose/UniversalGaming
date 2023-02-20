cmake_minimum_required(VERSION 3.5)

project(UniversalGamingApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS SerialPort Widgets Gui Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        customtabstyle.h
        console.h console.cpp
        settingswidget.h settingswidget.cpp settingswidget.ui
        terminalwindow.h terminalwindow.cpp terminalwindow.ui
        controllerlayout.h controllerlayout.cpp controllerlayout.ui
        customlayout.h customlayout.cpp customlayout.ui
)

list(APPEND CMAKE_PREFIX_PATH "~/Qt/6.4.1/mingw_64")

qt_add_executable(UniversalGamingApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

target_link_libraries(UniversalGamingApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt6::SerialPort
    Qt6::Gui
    Qt6::Core
)

set_target_properties(UniversalGamingApp PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS UniversalGamingApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(UniversalGamingApp)
endif()
