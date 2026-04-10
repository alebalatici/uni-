#ifndef COFETARIE5_MYLIST_H
#define COFETARIE5_MYLIST_H
#include "../domain/materie.h"

typedef void* TElem;
typedef void (*DestroyFunction)(TElem);
typedef void* (*CopyFunction)(TElem);

typedef struct {
    TElem* elements;
    int capacity;
    int length;
} MyList;

MyList* create_empty_list();

void add_element(MyList* list, TElem element);

TElem get_element(MyList* list, int poz);

/**
 *
 * @param list /Seteaza elementul element de pe pozitia poz
 * @param poz /pozitia pe care se seteaza elementul (int)
 * @param element /elementul dat (TElem)
 * @return /elementul care era anterior pe pozitia poz (int)
 */
TElem set_element(MyList* list, int poz, TElem element);

TElem remove_element_from_position(MyList* list, int poz);

MyList* copy_list(MyList* list, CopyFunction copy_function);

int size_list(MyList* list);

int find_by_name(MyList* list, char* name);

void destroy_list(MyList* list, DestroyFunction destroy_function);

void destroy_lista_materii(void* list);

MyList* copy_list_of_materii(MyList *list);

void add_element_extended(MyList *list, TElem element);

#endif //COFETARIE5_MYLIST_H