cmake_minimum_required(VERSION 3.28)
project(Doctori)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Doctori main.cpp
        domain/doctor.h
        repo/repo_doctor.cpp
        repo/repo_doctor.h
        utils/file_utils.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        tests/tests_repo.cpp
        service/service_doctor.h
        tests/tests_service.cpp
        tests/tests_service.h
        gui/gui.cpp
        gui/gui.h)

target_link_libraries(Doctori PRIVATE Qt6::Widgets)