#include "tests_service.h"
#include <stdio.h>
#include <assert.h>

void test_srv_add_calatorie() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator3", 100);

    assert(size_list(test_list) == 3);
    assert(strcmp(((Materie*)get_element(test_list, 0))->nume, "Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 1))->nume, "Nume2") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 2))->nume, "Nume3") == 0);

    assert(strcmp(((Materie*)get_element(test_list, 0))->producator, "Producator1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 1))->producator, "Producator2") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 2))->producator, "Producator3") == 0);

    assert(((Materie*)get_element(test_list, 0))->cantitate == 50);
    assert(((Materie*)get_element(test_list, 1))->cantitate == 50);
    assert(((Materie*)get_element(test_list, 2))->cantitate == 100);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_srv_delete_calatorie() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list,"Nume3", "Producator3", 100);

    assert(size_list(test_list) == 3);

    int ok = srv_delete_calatorie(test_list, undo_list, "Nume1");
    assert(size_list(test_list) == 2);
    ok = srv_delete_calatorie(test_list, undo_list, "Nume2");
    assert(size_list(test_list) == 1);
    ok = srv_delete_calatorie(test_list, undo_list,"Nume3");
    assert(size_list(test_list) == 0);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_filter_by_name() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator3", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4", 560);
    srv_add_calatorie(test_list, undo_list, "Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "A_Nume3", "Producator6", 1070);
    srv_add_calatorie(test_list, undo_list, "A_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator9", 1100);
    assert(size_list(test_list) == 7);
    MyList* test_list2 = filter_by_name(test_list, 'N');
    assert(size_list(test_list2) == 3);
    assert(strcmp(((Materie*)get_element(test_list2, 0))->nume, "Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list2, 1))->nume, "Nume3") == 0);
    assert(strcmp(((Materie*)get_element(test_list2, 2))->nume, "Nume2") == 0);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
    destroy_list(test_list2, destroy_materie);
}

void test_filter_by_quantity() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator3", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4", 560);
    srv_add_calatorie(test_list, undo_list, "Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "A_Nume3", "Producator6", 1070);
    srv_add_calatorie(test_list, undo_list, "A_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator9", 1100);
    assert(size_list(test_list) == 7);
    MyList* test_list2 = filter_by_quantity(test_list, 502);
    assert(size_list(test_list2) == 5);

    MyList* test_list3 = filter_by_quantity(test_list, 1100);
    assert(size_list(test_list3) == 1);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
    destroy_list(test_list2, destroy_materie);
    destroy_list(test_list3, destroy_materie);
}

void test_sort_by_quantity() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator3", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4", 560);
    srv_add_calatorie(test_list, undo_list, "Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "A_Nume3", "Producator6", 1070);
    srv_add_calatorie(test_list, undo_list, "A_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "Nume3", "Producator9", 1100);

    sort_by_quantity(test_list);

    assert(size_list(test_list) == 7);
    assert(strcmp(((Materie*)get_element(test_list, 0))->nume, "Nume1") == 0);
    assert(((Materie*)get_element(test_list, 0))->cantitate == 50);
    assert(((Materie*)get_element(test_list, 1))->cantitate == 200);
    assert(((Materie*)get_element(test_list, 2))->cantitate == 502);
/*
    for (int i = 0; i < test_list->length; i++) {
        Materie* m = test_list->elements[i];
        printf("Nume: %s | Producator: %s | Cantitate: %d", m->nume, m->producator, m->cantitate);
        printf("\n");
    }
    printf("\n");
*/
    assert(((Materie*)get_element(test_list, 3))->cantitate == 506);
    assert(strcmp(((Materie*)get_element(test_list, 3))->nume, "Nume2") == 0);
    assert(((Materie*)get_element(test_list, 4))->cantitate == 560);
    assert(((Materie*)get_element(test_list, 5))->cantitate == 1070);
    assert(((Materie*)get_element(test_list, 6))->cantitate == 1110);
    assert(strcmp(((Materie*)get_element(test_list, 6))->nume, "Nume3") == 0);
    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_sort_by_name() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "I_Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "H_Nume3", "Producator3", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4", 560);
    srv_add_calatorie(test_list, undo_list, "G_Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "C_Nume3", "Producator6", 1070);
    srv_add_calatorie(test_list, undo_list, "D_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "E_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "F_Nume3", "Producator9", 1100);

    sort_by_name(test_list);
    assert(strcmp(((Materie*)get_element(test_list, 0))->nume, "A_Nume2") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 1))->nume, "B_Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 2))->nume, "C_Nume3") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 3))->nume, "D_Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 4))->nume, "E_Nume2") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 5))->nume, "F_Nume3") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 6))->nume, "G_Nume2") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 7))->nume, "H_Nume3") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 8))->nume, "I_Nume1") == 0);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_modify_element() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "I_Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2", 50);
    srv_add_calatorie(test_list, undo_list, "H_Nume3", "Producator3", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4", 560);
    srv_add_calatorie(test_list, undo_list, "G_Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "C_Nume3", "Producator6", 1070);
    srv_add_calatorie(test_list, undo_list, "D_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "E_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "F_Nume3", "Producator9", 1100);
    assert(size_list(test_list) == 9);

    assert(strcmp(((Materie*)get_element(test_list, 0))->nume, "I_Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 0))->producator, "Producator1") == 0);
    assert(((Materie*)get_element(test_list, 0))->cantitate == 50);
    int result = modify_element(test_list, undo_list, "I_Nume1", "Producator2", 100);
    assert(strcmp(((Materie*)get_element(test_list, 0))->nume, "I_Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list, 0))->producator, "Producator2") == 0);
    assert(((Materie*)get_element(test_list, 0))->cantitate == 100);

    result = modify_element(test_list, undo_list, "ThisItemDoesNotExist", "Producator2", 100);
    assert(result == -4);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_count_vowels_in_word() {
    assert(count_vowels_in_word("plant") == 1);
    assert(count_vowels_in_word("basin") == 2);
    assert(count_vowels_in_word("proud") == 2);
    assert(count_vowels_in_word("matrix") == 2);
    assert(count_vowels_in_word("hide") == 2);
    assert(count_vowels_in_word("payment") == 2);
    assert(count_vowels_in_word("queue") == 4);
    assert(count_vowels_in_word("hover") == 2);
    assert(count_vowels_in_word("linen") == 2);
    assert(count_vowels_in_word("medieval") == 4);
}

void test_filter_by_producator() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();
    srv_add_calatorie(test_list, undo_list, "I_Nume1", "Producator1", 50);
    srv_add_calatorie(test_list, undo_list, "A_Nume2", "Producator2OU", 50);
    srv_add_calatorie(test_list, undo_list, "H_Nume3", "Producator3F", 10);
    srv_add_calatorie(test_list, undo_list, "B_Nume1", "Producator4I", 560);
    srv_add_calatorie(test_list, undo_list, "G_Nume2", "Producator5", 506);
    srv_add_calatorie(test_list, undo_list, "C_Nume3", "Producator6E", 1070);
    srv_add_calatorie(test_list, undo_list, "D_Nume1", "Producator7", 502);
    srv_add_calatorie(test_list, undo_list, "E_Nume2", "Producator8", 150);
    srv_add_calatorie(test_list, undo_list, "F_Nume3", "Producator9A", 1100);

    MyList* test_list2 = filter_by_producator(test_list, 7);
    assert(size_list(test_list2) == 0);
    destroy_list(test_list2, destroy_materie);

    MyList* test_list3 = filter_by_producator(test_list, 4);
    assert(size_list(test_list3) == 9);
    destroy_list(test_list3, destroy_materie);

    MyList* test_list4 = filter_by_producator(test_list, 5);
    assert(size_list(test_list4) == 4);
    destroy_list(test_list4, destroy_materie);

    MyList* test_list5 = filter_by_producator(test_list, 6);
    assert(size_list(test_list5) == 1);
    destroy_list(test_list5, destroy_materie);

    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}

void test_all_service() {
    test_srv_add_calatorie();
    test_srv_delete_calatorie();
    test_filter_by_name();
    test_filter_by_quantity();
    test_sort_by_quantity();
    test_sort_by_name();
    test_modify_element();
    test_count_vowels_in_word();
    test_filter_by_producator();
    printf("Testele din service au trecut cu succes!\n");
}