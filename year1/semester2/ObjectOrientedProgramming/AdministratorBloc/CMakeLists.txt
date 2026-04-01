cmake_minimum_required(VERSION 3.28)
project(AdministratorBloc)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdministratorBloc main.cpp
        domain/locatar.cpp
        domain/locatar.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        tests/tests_domain.cpp
        tests/tests_domain.h
        repo/repo_locatari.cpp
        repo/repo_locatari.h
        tests/tests_repo.cpp
        tests/tests_repo.h
        service/service_locatari.cpp
        service/service_locatari.h
        domain/validator.cpp
        domain/validator.h
        tests/tests_service.cpp
        tests/tests_service.h
        ui/ui.cpp
        ui/ui.h)
