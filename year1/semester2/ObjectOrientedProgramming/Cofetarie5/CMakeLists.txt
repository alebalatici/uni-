cmake_minimum_required(VERSION 3.28)
project(Cofetarie5 C)

set(CMAKE_C_STANDARD 17)

add_executable(Cofetarie5 main.c
        domain/materie.c
        domain/materie.h
        tests/tests_domain.c
        tests/tests_domain.h
        repo/mylist.c
        repo/mylist.h
        tests/tests_mylist.c
        tests/tests_mylist.h
        srv/service.c
        srv/service.h
        domain/validator.c
        domain/validator.h
        ui/console.c
        ui/console.h
        tests/tests_service.c
        tests/tests_service.h
        undo/undo.c
        undo/undo.h
        tests/tests_undo.c
        tests/tests_undo.h)
