cmake_minimum_required(VERSION 3.28)
project(Melodii)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Melodii main.cpp
        domain/melodie.cpp
        domain/melodie.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        domain/validator.cpp
        domain/validator.h
        repo/repo_melodii.cpp
        repo/repo_melodii.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        utils/file_utils.cpp
        utils/file_utils.h
        service/service_melodii.cpp
        service/service_melodii.h
        tests/tests_service.cpp
        tests/tests_service.h
        gui/gui.cpp
        gui/gui.h
        gui/my_table.cpp
        gui/my_table.h
        observer/observer.cpp
        observer/observer.h
        gui/histogram_widget.cpp
        gui/histogram_widget.h)

target_link_libraries(Melodii PRIVATE Qt6::Widgets)