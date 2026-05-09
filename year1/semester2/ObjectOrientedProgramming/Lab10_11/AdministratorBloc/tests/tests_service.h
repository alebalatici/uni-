#ifndef ADMINISTRATORBLOC_TESTS_SERVICE_H
#define ADMINISTRATORBLOC_TESTS_SERVICE_H
#include "../service/service_locatari.h"
#include <cassert>
#include <iostream>
class TestsService {
private:
    static void test_add_locatar();
    static void test_get_all_locatari();
    static void test_delete_locatar();
    static void test_find_locatar();
    static void test_modify_locatar();
    static void test_count_vowels();
    static void test_filter_after_type();
    static void test_filter_after_surface();
    static void test_sort_after_name();
    static void test_sort_after_surface();
    static void test_sort_after_type_and_surface();

    static void test_list_add_notificare();
    static void test_list_empty_full();
    static void test_list_add_random_notificari();
    static void test_undo();
public:
    static void test_all_service();
};

#endif //ADMINISTRATORBLOC_TESTS_SERVICE_H