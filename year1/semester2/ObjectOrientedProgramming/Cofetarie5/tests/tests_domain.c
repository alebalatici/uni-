#include "tests_domain.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
void test_create_materie() {
    Materie* materie = create_materie("Nume1", "Producator1", 50);
    assert(strcmp(materie->nume, "Nume1") == 0);
    assert(strcmp(materie->producator, "Producator1") == 0);
    assert(materie->cantitate == 50);

    Materie* materie1 = create_materie("Nume2", "Producator2", 50);
    assert(strcmp(materie1->nume, "Nume2") == 0);
    assert(strcmp(materie1->producator, "Producator2") == 0);
    assert(materie1->cantitate == 50);

    Materie* materie2 = create_materie("Nume3", "Producator3", 100);
    assert(strcmp(materie2->nume, "Nume3") == 0);
    assert(strcmp(materie2->producator, "Producator3") == 0);
    assert(materie2->cantitate == 100);

    destroy_materie(materie);
    destroy_materie(materie1);
    destroy_materie(materie2);
}

void test_destroy_materie() {
    Materie* materie = create_materie("Nume1", "Producator1", 50);
    Materie* materie1 = create_materie("Nume2", "Producator2", 50);
    Materie* materie2 = create_materie("Nume3", "Producator3", 100);
    destroy_materie(materie);
    destroy_materie(materie1);
    destroy_materie(materie2);
}

void test_copy_materie() {
    Materie* materie = create_materie("Nume1", "Producator1", 50);
    Materie* materie1 = copy_materie(materie);
    assert(strcmp(materie1->nume, "Nume1") == 0);
    assert(strcmp(materie1->producator, "Producator1") == 0);
    assert(materie1->cantitate == 50);

    destroy_materie(materie);
    destroy_materie(materie1);
}

void test_validator() {
    Materie* m = create_materie("a", "Producator1", 50);
    assert(valideaza_materie(m) == -1);
    Materie* m1 = create_materie("Nume1", "P", 50);
    assert(valideaza_materie(m1) == -2);
    Materie* m2 = create_materie("Nume2", "Producator2", -50);
    assert(valideaza_materie(m2) == -3);
    Materie* m3 = create_materie("Nume3", "Producator3", 50);
    assert(valideaza_materie(m3) == 0);

    destroy_materie(m);
    destroy_materie(m1);
    destroy_materie(m2);
    destroy_materie(m3);
}

void test_all_domain() {
    test_create_materie();
    test_destroy_materie();
    test_validator();
    test_copy_materie();
    printf("Testele au rulat cu succes!\n");
}