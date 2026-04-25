#ifndef ADMINISTRATORBLOC_TESTS_LISTA_NOTIFICARE_H
#define ADMINISTRATORBLOC_TESTS_LISTA_NOTIFICARE_H

#include <cassert>
#include "../domain/locatar.h"
#include "../notification_list/lista_notificare.h"

class TestsListaNotificare {
    private:
    static void test_add_notificare();
    static void test_empty_list();
    static void test_add_random_notificari();
    public:
    static void test_all_lista_notificare();
};



#endif //ADMINISTRATORBLOC_TESTS_LISTA_NOTIFICARE_H
