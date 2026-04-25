#ifndef ADMINISTRATORBLOC_TESTS_DOMAIN_H
#define ADMINISTRATORBLOC_TESTS_DOMAIN_H
#include "../domain/locatar.h"
#include "../domain/validator.h"
#include <cassert>
#include <string>
using std::string;

class TestsDomain {
private:
    static void test_get_domain();
    static void test_set_domain();
    static void test_validator();
public:
    static void test_all_domain();

};

#endif //ADMINISTRATORBLOC_TESTS_DOMAIN_H