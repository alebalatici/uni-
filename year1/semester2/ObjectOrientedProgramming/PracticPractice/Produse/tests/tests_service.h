//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_TESTS_SERVICE_H
#define PRODUSE_TESTS_SERVICE_H

#include <cassert>
#include "../domain/validator.h"
#include "../repo/repo_produs.h"
#include "../utils/file_utils.h"
#include "../service/service_produs.h"
class TestsService {
private:
    static void test_add_produs();
    static void test_delete_produs();
    static void test_modify_produs();
    static void test_find_produs();
    static void test_sort_by_price();
public:
    static void test_all_service();
};



#endif //PRODUSE_TESTS_SERVICE_H
