#include "undo.h"

MyList* undo(MyList* current_list, MyList* undo_list) {
    if (undo_list->length == 0) {
        return current_list;
    }
    MyList* last = undo_list->elements[undo_list->length - 1];
    undo_list->length--;
    destroy_list(current_list, destroy_materie);

    current_list = last;
    return current_list;
}