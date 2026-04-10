#ifndef COFETARIE5_SERVICE_H
#define COFETARIE5_SERVICE_H
#include "../repo/mylist.h"
#include "../domain/validator.h"
#include "../undo/undo.h"

int srv_add_calatorie(MyList* list, MyList* undo_list, char* nume, char* producator, int cantitate);

int srv_delete_calatorie(MyList* list,  MyList* undo_list, char* nume);

MyList* filter_by_name(MyList* list, char name);

MyList* filter_by_quantity(MyList* list, int quantity);

MyList* filter_by_producator(MyList* list, int minimum_vowels);

void sort_by_quantity(MyList* list);

void sort_by_name(MyList* list);

int modify_element(MyList* list, MyList* undo_list, char* nume, char* producator, int cantitate);

int count_vowels_in_word(char* word);

#endif //COFETARIE5_SERVICE_H