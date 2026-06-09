//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_TESTS_REPO_H
#define PRODUSE_TESTS_REPO_H

#include <cassert>
#include "../repo/repo_produs.h"
class TestsRepo {
private:
    static void test_add_produs();
    static void test_delete_produs();
    static void test_modify_produs();
    static void test_find_produs();

    static void test_file_add_produs();
    static void test_file_delete_produs();
    static void test_file_modify_produs();
    static void test_file_find_produs();
public:
    static void test_all_repo();
};



#endif //PRODUSE_TESTS_REPO_H
