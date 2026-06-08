//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_TESTS_DOMAIN_H
#define MELODII_TESTS_DOMAIN_H

#include <string>
#include <cassert>
#include "../domain/melodie.h"
#include "../domain/validator.h"
class TestsDomain {
private:
    static void test_get_domain();
    static void test_set_domain();
    static void test_validator();
public:
    static void test_all_domain();
};



#endif //MELODII_TESTS_DOMAIN_H
