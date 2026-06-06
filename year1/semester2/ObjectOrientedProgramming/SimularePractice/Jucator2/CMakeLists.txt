cmake_minimum_required(VERSION 3.28)
project(Jucator2)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Jucator2 main.cpp
        domain/jucator.h
        repo/repo_jucatori.cpp
        repo/repo_jucatori.h
        service/service_jucatori.cpp
        service/service_jucatori.h
        tests/tests.cpp
        tests/tests.h
        gui/gui.cpp
        gui/gui.h)

target_link_libraries(Jucator2 PRIVATE Qt6::Widgets)