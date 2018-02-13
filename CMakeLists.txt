cmake_minimum_required(VERSION 3.8)
project(TP1)

set (CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/")
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)


set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ig1-1.png
        ig1-10.png
        ig1-11.png
        ig1-12.png
        ig1-2.png
        ig1-3.png
        ig1-4.png
        ig1-5.png
        ig1-6.png
        ig1-7.png
        ig1-8.png
        ig1-9.png
        main.cpp
        tp-ig-1.dox
        tref.tri
        Viewer.cpp
        Viewer.h
        viewer.pro Utils.cpp Utils.hpp)

add_executable(TP1 ${SOURCE_FILES})