cmake_minimum_required(VERSION 3.28)
project(AdministratorBloc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(AdministratorBloc
        main.cpp
        domain/locatar.cpp
        domain/locatar.h
        domain/validator.cpp
        domain/validator.h
        repo/repo_locatari.cpp
        repo/repo_locatari.h
        service/service_locatari.cpp
        service/service_locatari.h
        ui/ui.cpp
        ui/ui.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        tests/tests_service.cpp
        tests/tests_service.h
        notification_list/lista_notificare.cpp
        notification_list/lista_notificare.h
        tests/tests_lista_notificare.cpp
        tests/tests_lista_notificare.h
        utils/file_utils.cpp
        utils/file_utils.h
        undo/undo.h
)

target_compile_options(AdministratorBloc PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
)

target_compile_options(AdministratorBloc PRIVATE
        -Werror
)