#include "mylist.h"

#include <stdlib.h>

MyList *create_empty_list() {
    MyList *list = malloc(sizeof(MyList));
    list->capacity = 2;
    list->elements = malloc(list->capacity * sizeof(TElem));
    list->length = 0;
    return list;
}

void add_element(MyList *list, TElem element) {
    Materie *new_elem = (Materie *) element;
    for (int i = 0; i < list->length; i++) {
        Materie *curent = (Materie *) list->elements[i];
        if (strcmp(curent->nume, new_elem->nume) == 0) {
            int new_quantity = curent->cantitate + new_elem->cantitate;
            curent->cantitate = new_quantity;
            destroy_materie(new_elem);
            return;
        }
    }
    if (list->length == list->capacity) {
        int new_capacity = list->capacity * 2;
        TElem *new_elements = malloc(new_capacity * sizeof(TElem));
        for (int i = 0; i < list->length; i++) {
            new_elements[i] = list->elements[i];
        }
        free(list->elements);
        list->elements = new_elements;
        list->capacity = new_capacity;
    }
    list->elements[list->length++] = element;
}

void add_element_extended(MyList *list, TElem element) {
    if (list->length == list->capacity) {
        int new_capacity = list->capacity * 2;
        TElem *new_elements = malloc(new_capacity * sizeof(TElem));
        for (int i = 0; i < list->length; i++) {
            new_elements[i] = list->elements[i];
        }
        free(list->elements);
        list->elements = new_elements;
        list->capacity = new_capacity;
    }
    list->elements[list->length++] = element;
}

TElem get_element(MyList *list, int poz) {
    return list->elements[poz];
}

TElem set_element(MyList *list, int poz, TElem element) {
    TElem old_element = list->elements[poz];
    list->elements[poz] = element;
    return old_element;
}

TElem remove_element_from_position(MyList *list, int poz) {
    TElem old_element = list->elements[poz];
    for (int i = poz; i < list->length - 1; i++) {
        list->elements[i] = list->elements[i + 1];
    }
    list->length--;
    return old_element;
}

int find_by_name(MyList *list, char *name) {
    for (int i = 0; i < size_list(list); i++) {
        Materie *curent = (Materie *) get_element(list, i);
        if (strcmp(curent->nume, name) == 0) {
            return i;
        }
    }
    return -1;
}

MyList* copy_list_of_materii(MyList *list) {
    return copy_list(list, (void*)copy_materie);
}

MyList *copy_list(MyList *list, CopyFunction copy_function) {
    MyList *new_list = create_empty_list();
    for (int i = 0; i < list->length; i++) {
        TElem elem = get_element(list, i);
        add_element(new_list, copy_function(elem));
    }
    return new_list;
}

void destroy_lista_materii(void *list) {
    destroy_list(list, destroy_materie);
}

void destroy_list(MyList *list, DestroyFunction destroy_function) {
    for (int i = 0; i < list->length; i++) {
        TElem element = list->elements[i];
        destroy_function(element);
    }
    free(list->elements);
    list->length = 0;
    list->capacity = 0;
    free(list);
}

int size_list(MyList *list) {
    return list->length;
}
