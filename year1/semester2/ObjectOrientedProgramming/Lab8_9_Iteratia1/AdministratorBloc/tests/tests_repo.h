#ifndef ADMINISTRATORBLOC_TESTS_REPO_H
#define ADMINISTRATORBLOC_TESTS_REPO_H
#include "../repo/repo_locatari.h"
#include <assert.h>

class TestsRepo {
private:
    static void test_add_locatar();
    static void test_get_all_locatari();
    static void test_delete_locatar();
    static void test_find_locatar();
    static void test_modify_locatar();
public:
    static void test_all_repo();
};

#endif //ADMINISTRATORBLOC_TESTS_REPO_H