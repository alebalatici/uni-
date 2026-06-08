//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_TESTS_REPO_H
#define MELODII_TESTS_REPO_H

#include <cassert>
#include "../repo/repo_melodii.h"
#include "../utils/file_utils.h"
class TestsRepo {
private:
    static void test_add_melodie();
    static void test_delete_melodie() ;
    static void test_modify_melodie();
    static void test_find_melodie();

    static void test_file_add_melodie();
    static void test_file_delete_melodie() ;
    static void test_file_modify_melodie();
    static void test_file_find_melodie();
public:
    static void test_all_repo();
};

#endif //MELODII_TESTS_REPO_H
