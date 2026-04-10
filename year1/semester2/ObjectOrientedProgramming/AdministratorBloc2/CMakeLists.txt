cmake_minimum_required(VERSION 3.28)
project(AdministratorBloc)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdministratorBloc main.cpp
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
        vector/myvector.h
        tests/tests_myvector.cpp
        tests/tests_myvector.h
        )
