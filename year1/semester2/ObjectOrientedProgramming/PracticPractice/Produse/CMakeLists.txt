cmake_minimum_required(VERSION 3.28)
project(Produse)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Produse main.cpp
        domain/produs.cpp
        domain/produs.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        domain/validator.cpp
        domain/validator.h
        repo/repo_produs.cpp
        repo/repo_produs.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        utils/file_utils.cpp
        utils/file_utils.h
        service/service_produs.cpp
        service/service_produs.h
        tests/tests_service.cpp
        tests/tests_service.h
        gui/gui.cpp
        gui/gui.h
        gui/my_table.cpp
        gui/my_table.h
        gui/my_list.cpp
        gui/my_list.h
        observer/observer.cpp
        observer/observer.h
        gui/type_window.cpp
        gui/type_window.h)

target_link_libraries(Produse PRIVATE Qt6::Widgets)