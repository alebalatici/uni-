cmake_minimum_required(VERSION 3.28)
project(Jucator)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Jucator main.cpp
        domain/jucator.h
        repo/repo_jucatori.cpp
        repo/repo_jucatori.h
        utils/file_utils.h
        tests/tests.h
        service/service_jucatori.h
        gui/gui.cpp
        gui/gui.h)

target_link_libraries(Jucator PRIVATE Qt6::Widgets)