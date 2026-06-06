cmake_minimum_required(VERSION 3.28)
project(Jucator3)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Jucator3 main.cpp
        domain/jucator.cpp
        domain/jucator.h
        repo/repo_jucator.cpp
        repo/repo_jucator.h
        service/service_jucator.cpp
        service/service_jucator.h
        gui/gui.cpp
        gui/gui.h
        tests/tests.cpp
        tests/tests.h)

target_link_libraries(Jucator3 PRIVATE Qt6::Widgets)