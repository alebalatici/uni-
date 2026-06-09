//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_TESTS_DOMAIN_H
#define PRODUSE_TESTS_DOMAIN_H

#include <cassert>
#include "../domain/produs.h"

class TestsDomain {
    private:
    static void test_get();
    static void test_set();
    static void test_validator();
    public:
    static void test_all_domain();
};



#endif //PRODUSE_TESTS_DOMAIN_H
