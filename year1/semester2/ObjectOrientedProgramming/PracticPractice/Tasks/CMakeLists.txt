cmake_minimum_required(VERSION 3.28)
project(Tasks)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(Tasks main.cpp
        domain/task.cpp
        domain/task.h
        repository/repo_tasks.cpp
        repository/repo_tasks.h
        tests/tests.cpp
        tests/tests.h
        service/srv_tasks.cpp
        service/srv_tasks.h
        gui/gui.cpp
        gui/gui.h
        gui/my_table.cpp
        gui/my_table.h
        domain/validator.cpp
        domain/validator.h
        gui/my_list_string.cpp
        gui/my_list_string.h
        observer/observer.cpp
        observer/observer.h
        gui/task_window.cpp
        gui/task_window.h
        )

target_link_libraries(Tasks PRIVATE Qt6::Widgets)