#include "tests_mylist.h"
#include <stdio.h>
#include <assert.h>
void test_create_empty_list() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    destroy_list(test_list, destroy_materie);
}

void test_add_element() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    add_element(test_list, materie1);
    assert(test_list->length == 1);
    assert(test_list->capacity == 2);

    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    add_element(test_list, materie2);
    assert(test_list->length == 2);
    assert(test_list->capacity == 2);

    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie3);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);

    Materie* materie4 = create_materie("Nume1", "Producator4", 100);
    add_element(test_list, materie4);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);
    Materie* materie5 = get_element(test_list, 0);

    assert(strcmp(materie5->nume, "Nume1") == 0);
    assert(strcmp(materie5->producator, "Producator1") == 0);
    assert(materie5->cantitate == 150);

    destroy_list(test_list, destroy_materie);
}

void test_get_element() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);
    Materie* m1 = get_element(test_list, 0);
    assert(strcmp(m1->nume, "Nume1") == 0);
    assert(strcmp(m1->producator, "Producator1") == 0);
    assert(m1->cantitate == 50);

    Materie* m2 = get_element(test_list, 1);
    assert(strcmp(m2->nume, "Nume2") == 0);
    assert(strcmp(m2->producator, "Producator2") == 0);
    assert(m2->cantitate == 50);

    Materie* m3 = get_element(test_list, 2);
    assert(strcmp(m3->nume, "Nume3") == 0);
    assert(strcmp(m3->producator, "Producator3") == 0);
    assert(m3->cantitate == 100);

    destroy_list(test_list, destroy_materie);
}

void test_set_element() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);

    Materie* m4 = create_materie("Nume4", "Producator4", 100);
    Materie* m1 = set_element(test_list, 0, m4);
    assert(strcmp(m1->nume, "Nume1") == 0);
    assert(strcmp(m1->producator, "Producator1") == 0);
    assert(m1->cantitate == 50);

    Materie* m2 = get_element(test_list, 0);
    assert(strcmp(m2->nume, "Nume4") == 0);
    assert(strcmp(m2->producator, "Producator4") == 0);
    assert(m2->cantitate == 100);

    destroy_list(test_list, destroy_materie);

    destroy_materie(m1);
}

void test_remove_element_from_position() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);

    Materie* m1 = remove_element_from_position(test_list, 0);
    assert(strcmp(m1->nume, "Nume1") == 0);
    assert(strcmp(m1->producator, "Producator1") == 0);
    assert(m1->cantitate == 50);

    destroy_list(test_list, destroy_materie);
    destroy_materie(m1);
}

void test_copy_list() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);
    assert(test_list->length == 3);
    assert(test_list->capacity == 4);

    MyList* test_list2 = copy_list(test_list, (void*)copy_materie);
    assert(test_list2->length == 3);
    assert(test_list2->capacity == 4);
    assert(strcmp(((Materie*)get_element(test_list2, 0))->nume, "Nume1") == 0);
    assert(strcmp(((Materie*)get_element(test_list2, 0))->producator, "Producator1") == 0);
    assert(((Materie*)get_element(test_list2, 0))->cantitate == 50);

    assert(strcmp(((Materie*)get_element(test_list2, 1))->nume, "Nume2") == 0);
    assert(strcmp(((Materie*)get_element(test_list2, 1))->producator, "Producator2") == 0);
    assert(((Materie*)get_element(test_list2, 1))->cantitate == 50);

    assert(strcmp(((Materie*)get_element(test_list2, 2))->nume, "Nume3") == 0);
    assert(strcmp(((Materie*)get_element(test_list2, 2))->producator, "Producator3") == 0);
    assert(((Materie*)get_element(test_list2, 2))->cantitate == 100);

    destroy_list(test_list2, destroy_materie);
    destroy_list(test_list, destroy_materie);
}


void test_destroy_list() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    destroy_list(test_list, destroy_materie);

    MyList* test_list2 = create_empty_list();
    assert(test_list2->length == 0);
    assert(test_list2->capacity == 2);
    destroy_list(test_list2, destroy_materie);
}

void test_size_list() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);
    assert(size_list(test_list) == 3);
    Materie* m1 = remove_element_from_position(test_list, 0);
    assert(size_list(test_list) == 2);
    destroy_list(test_list, destroy_materie);
    destroy_materie(m1);
}

void test_all_mylist() {
    test_create_empty_list();
    test_destroy_list();
    test_add_element();
    test_get_element();
    test_set_element();
    test_remove_element_from_position();
    test_copy_list();
    test_size_list();
    test_find_by_name();
    test_liste_de_liste();
    test_undo_list();
    printf("Testele din repo au trecut cu succes!\n");
}

void test_find_by_name() {
    MyList* test_list = create_empty_list();
    assert(test_list->length == 0);
    assert(test_list->capacity == 2);
    Materie* materie1 = create_materie("Nume1", "Producator1", 50);
    Materie* materie2 = create_materie("Nume2", "Producator2", 50);
    Materie* materie3 = create_materie("Nume3", "Producator3", 100);
    add_element(test_list, materie1);
    add_element(test_list, materie2);
    add_element(test_list, materie3);

    int poz1 = find_by_name(test_list, "Nume1");
    if (poz1 != 1)
    {
        assert(strcmp(((Materie*)get_element(test_list, poz1))->nume, "Nume1") == 0);
        assert(strcmp(((Materie*)get_element(test_list, poz1))->producator, "Producator1") == 0);
        assert(((Materie*)get_element(test_list, poz1))->cantitate == 50);
    }
    destroy_list(test_list, destroy_materie);
}

void test_liste_de_liste() {
    MyList* mylist = create_empty_list();
    MyList* undoList = create_empty_list();

    add_element(mylist, create_materie("Nume1", "Producator1", 5));
    add_element(mylist, create_materie("Nume2", "Producator2", 5));
    add_element(mylist, create_materie("Nume3", "Producator3", 100));
    assert(size_list(mylist) == 3);
    add_element(undoList, mylist);
    assert(size_list(undoList) == 1);

    destroy_list(undoList, destroy_lista_materii);
}


void test_undo_list() {
    MyList* test_list = create_empty_list();
    MyList* undo_list = create_empty_list();

    add_element(test_list, create_materie("Nume1", "Producator1", 5));
    add_element(test_list, create_materie("Nume2", "Producator2", 5));
    add_element(test_list, create_materie("Nume3", "Producator3", 100));

    assert(size_list(test_list) == 3);
    add_element_extended(undo_list, copy_list(test_list, (void*)copy_materie));
    assert(size_list(undo_list) == 1);
    //test_list are 3 elemente
    //undo_list = test_list (test_list 3 elemente)
    add_element(test_list, create_materie("Nume4", "Producator2", 5));
    //test_list' are 4 elemente
    //undo_list = test_list (test_list 3 elemente)

    assert(size_list(undo_list) == 1);
    assert(size_list(test_list) == 4);

    test_list = undo(test_list, undo_list);

    assert(size_list(test_list) == 3);
    /*
        for (int i = 0; i < test_list->length; i++) {
            Materie* m = test_list->elements[i];
            printf("Nume: %s | Producator: %s | Cantitate: %d", m->nume, m->producator, m->cantitate);
            printf("\n");
        }
        printf("\n");
    */
    destroy_list(undo_list, destroy_lista_materii);
    destroy_list(test_list, destroy_materie);
}