cmake_minimum_required(VERSION 3.28)
project(Device)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Device main.cpp
        domain/device.h
        repo/repo_device.cpp
        repo/repo_device.h
        utils/file_utils.h
        tests/tests.h
        service/service_device.h
        gui/gui.cpp
        gui/gui.h)

target_link_libraries(Device PRIVATE Qt6::Widgets)