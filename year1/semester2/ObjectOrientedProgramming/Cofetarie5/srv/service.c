#include "service.h"
#include <string.h>

int srv_add_calatorie(MyList* list, MyList* undo_list,char* nume, char* producator, int cantitate) {
    Materie* m = create_materie(nume, producator, cantitate);

    int validation_code = valideaza_materie(m);

    if (validation_code != 0) {
        destroy_materie(m);
        return validation_code;
    }

    add_element_extended(undo_list, copy_list(list, (void*)copy_materie));
    add_element(list, m);
    return 0;
}

int modify_element(MyList* list,  MyList* undo_list, char* nume, char* producator, int cantitate) {
    int poz = find_by_name(list, nume);
    if (poz == -1)
        return -4;

    Materie* materie = create_materie(nume, producator, cantitate);
    int validation_code = valideaza_materie(materie);

    if (validation_code != 0) {
        destroy_materie(materie);
        return validation_code;
    }

    add_element_extended(undo_list, copy_list(list, (void*)copy_materie));
    Materie* m = set_element(list, poz, materie);
    destroy_materie(m);
    return 0;
}

int srv_delete_calatorie(MyList* list,  MyList* undo_list, char* nume) {
    int poz = find_by_name(list, nume);
    if (poz == -1)
        return -1;

    add_element_extended(undo_list, copy_list(list, (void*)copy_materie));
    Materie* deleted = remove_element_from_position(list, poz);
    destroy_materie(deleted);
    return 0;
}

MyList* filter_by_name(MyList* list, char name) {
    if (!name)
        return copy_list(list, (void*)copy_materie);

    MyList* new_list = create_empty_list();
    for (int i = 0; i < list->length; i++) {
        Materie* m = get_element(list, i);
        if (m->nume[0] == name)
            add_element(new_list, copy_materie(m));
    }
    return new_list;
}

MyList* filter_by_quantity(MyList* list, int quantity) {
    MyList* new_list = create_empty_list();
    for (int i = 0; i < list->length; i++) {
        Materie* m = get_element(list, i);
        if (m->cantitate >= quantity)
            add_element(new_list, copy_materie(m));
    }
    return new_list;
}

MyList* filter_by_producator(MyList* list, int minimum_vowels) {
    MyList* new_list = create_empty_list();
    for (int i = 0; i < list->length; i++) {
        Materie* m = get_element(list, i);
        if (count_vowels_in_word(m->producator) >= minimum_vowels)
            add_element(new_list, copy_materie(m));
    }
    return new_list;
}

void sort_by_quantity(MyList* list) {
    for (int i = 0; i < list->length - 1; i++) {
        for (int j = i + 1; j < list->length; j++) {
            Materie* elem_i = (Materie*)get_element(list, i);
            Materie* elem_j = (Materie*)get_element(list, j);
            if (elem_i->cantitate > elem_j->cantitate) {
                Materie* aux = list->elements[i];
                list->elements[i] = list->elements[j];
                list->elements[j] = aux;
            }
        }
    }
}

void sort_by_name(MyList* list) {
    for (int i = 0; i < list->length - 1; i++) {
        for (int j = i + 1; j < list->length; j++) {
            Materie* elem_i = (Materie*)get_element(list, i);
            Materie* elem_j = (Materie*)get_element(list, j);
            if (elem_i->nume[0] > elem_j->nume[0]) {
                Materie* aux = list->elements[i];
                list->elements[i] = list->elements[j];
                list->elements[j] = aux;
            }
        }
    }
}

int count_vowels_in_word(char* word) {
    int count = 0;
    for (int i = 0; i < strlen(word); i++) {
        if (strchr("aeiouAEIOU", word[i])) {
            count++;
        }
    }
    return count;
}