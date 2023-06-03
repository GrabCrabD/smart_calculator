cmake_minimum_required(VERSION 3.5)

project(smart_calc VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        qcustomplot.cpp
        qcustomplot.h

        calc.c
        stack.c
        s21_smart_calc.c
        s21_smart_calc.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smart_calc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(smart_calc SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(smart_calc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(smart_calc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(smart_calc PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(smart_calc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS smart_calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smart_calc)
endif()
