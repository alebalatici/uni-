#ifndef ADMINISTRATORBLOC_UI_H
#define ADMINISTRATORBLOC_UI_H
#include <iostream>
#include <limits>
#include "../service/service_locatari.h"
class Console {
    ServiceLocatari& srv;
public:
    Console(ServiceLocatari& srv) : srv{srv} {

    }

    static bool YesNoMenu();

    static void print_menu();

    static void print_all_locatari(const vector<Locatar>& locatari) ;

    void add_locatar_ui() const;

    void delete_locatar_ui() const;

    void modify_locatar_ui() const;

    void find_locatar_ui() const;

    static void filter_after_type_ui(const vector<Locatar>& list) ;

    static void filter_after_surface_ui(const vector<Locatar>& list) ;

    static void sort_after_name_ui(const vector<Locatar>& list);

    static void sort_after_surface_ui(const vector<Locatar>& list);

    static void sort_after_type_and_surface_ui(const vector<Locatar>& list);

    void run() const;
};

#endif //ADMINISTRATORBLOC_UI_H