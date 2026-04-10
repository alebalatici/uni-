#ifndef ADMINISTRATORBLOC_TESTS_MYVECTOR_H
#define ADMINISTRATORBLOC_TESTS_MYVECTOR_H

#include <cassert>
#include "../vector/myvector.h"
#include "../domain/locatar.h"

class TestsMyVector
{
    private:
    static void test_resize_push_back_size_capacity_empty();
    static void test_at();
    static void test_operator();
    static void test_begin_end();
    static void test_erase();
    static void test_copy_and_equal();

public:
    static void test_all_myvector();
};

#endif //ADMINISTRATORBLOC_TESTS_MYVECTOR_H
