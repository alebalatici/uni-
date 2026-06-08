//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_TESTS_SERVICE_H
#define MELODII_TESTS_SERVICE_H

#include <cassert>
#include "../service/service_melodii.h"
class TestsService {
private:
    static void test_add_melodie();
    static void test_delete_melodie();
    static void test_modify_melodie();
    static void test_find_melodie();
public:
    static void test_all_service();
};



#endif //MELODII_TESTS_SERVICE_H
