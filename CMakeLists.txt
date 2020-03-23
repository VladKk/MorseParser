cmake_minimum_required(VERSION 3.5)

project(MorseParser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/Qt/5.14.1/gcc_64/lib/cmake")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(MorseParser
        src/main.cpp
        src/mainwindow/mainwindow.cpp
        src/mainwindow/mainwindow.h
        src/mainwindow/mainwindow.ui
        res/resources.qrc
        )

target_link_libraries(MorseParser PRIVATE Qt5::Widgets)
