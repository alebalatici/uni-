cmake_minimum_required(VERSION 3.28)
project(GamingStore)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(GamingStore main.cpp
        domain/joc.h
        repo/repo_joc.cpp
        repo/repo_joc.h
        utils/file_utils.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        service/service_joc.h
        tests/tests_service.cpp
        tests/tests_service.h
        gui/gui.cpp
        gui/gui.h
        gui/gui.h)

target_link_libraries(GamingStore PRIVATE Qt6::Widgets)