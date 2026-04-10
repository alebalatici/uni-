#ifndef COFETARIE5_CONSOLE_H
#define COFETARIE5_CONSOLE_H
#include "../repo/mylist.h"
#include "../srv/service.h"

void print_menu();

void run();

void add_materie_ui(MyList* list, MyList* undo_list);

void print_all(MyList* list);

void print_menu_filtrare();

void filter_by_name_ui(MyList* list);

void filter_ui(MyList *list);

void sort_ui(MyList* list);

void delete_materie_ui(MyList* list, MyList* undo_list);

void modify_materie_ui(MyList* list, MyList* undo_list);

MyList* undo1_ui(MyList *list, MyList* undo_list);

void undo_ui(MyList **list, MyList* undo_list);

#endif //COFETARIE5_CONSOLE_H