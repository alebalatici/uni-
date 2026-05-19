cmake_minimum_required(VERSION 3.28)
project(TestOOP)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(TestOOP main.cpp
        domain/radiation.cpp
        domain/radiation.h
        domain/validator.cpp
        domain/validator.h
        repo/repo_radiation.cpp
        repo/repo_radiation.h
        tests/tests.cpp
        tests/tests.h
        service/service_radiation.cpp
        service/service_radiation.h
        gui/gui.cpp
        gui/gui.h
)

target_link_libraries(TestOOP PRIVATE Qt6::Widgets)