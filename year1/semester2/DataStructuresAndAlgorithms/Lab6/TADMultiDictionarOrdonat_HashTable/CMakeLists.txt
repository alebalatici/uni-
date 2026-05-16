cmake_minimum_required(VERSION 3.28)
project(TADMultiDictionarOrdonat_HashTable)

set(CMAKE_CXX_STANDARD 20)

add_executable(TADMultiDictionarOrdonat_HashTable
        "Proiect C++/App.cpp"
        "Proiect C++/IteratorMDO.cpp"
        "Proiect C++/IteratorMDO.h"
        "Proiect C++/MDO.cpp"
        "Proiect C++/MDO.h"
        Teste/TestExtins.cpp
        Teste/TestExtins.h
        Teste/TestScurt.cpp
        Teste/TestScurt.h)
