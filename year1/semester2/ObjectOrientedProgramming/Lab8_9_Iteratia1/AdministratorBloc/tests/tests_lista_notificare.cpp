#include "tests_lista_notificare.h"

void TestsListaNotificare::test_add_notificare()
{
    ListaNotificare lista_notificare;

    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    assert(lista_notificare.get_all_notificari().empty() == true);

    lista_notificare.add_notificare(l1);
    lista_notificare.add_notificare(l2);
    lista_notificare.add_notificare(l3);

    assert(lista_notificare.get_all_notificari().size() == 3);
    assert(lista_notificare.get_all_notificari()[0] == l1);
    assert(lista_notificare.get_all_notificari()[1] == l2);
    assert(lista_notificare.get_all_notificari()[2] == l3);
    assert(lista_notificare.get_all_notificari().empty() == false);
}

void TestsListaNotificare::test_empty_list()
{
    ListaNotificare lista_notificare;

    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    assert(lista_notificare.get_all_notificari().empty());

    lista_notificare.add_notificare(l1);
    lista_notificare.add_notificare(l2);
    lista_notificare.add_notificare(l3);
    assert(lista_notificare.get_all_notificari().size() == 3);
    assert(lista_notificare.get_all_notificari().empty() == false);

    lista_notificare.empty_list();
    assert(lista_notificare.get_all_notificari().empty() == true);
}

void TestsListaNotificare::test_add_random_notificari()
{
    ListaNotificare lista_notificare;

    vector<Locatar> original_lista_notificare = {
        Locatar{12324, "A", 1324.4, "B"},
        Locatar{2343, "Ab", 3454.4, "C"},
        Locatar{8765, "Abc", 6567.7, "D"},
        Locatar{43256, "Abc", 9878.7, "F"},
        Locatar{35657, "Abc", 687787.7, "G"},
    };

    lista_notificare.add_random_notificari(original_lista_notificare, 3);
    assert(lista_notificare.get_all_notificari().size() == 3);
    assert(lista_notificare.get_all_notificari().empty() == false);

    try
    {
        lista_notificare.add_random_notificari(original_lista_notificare, 100);
        assert(false);
    }
    catch(ListaNotificareException&)
    {
        assert(true);
    }

    lista_notificare.add_random_notificari(original_lista_notificare, 5);
    assert(lista_notificare.get_all_notificari().size() == 8);
    assert(lista_notificare.get_all_notificari().empty() == false);

    lista_notificare.add_random_notificari(original_lista_notificare, 1);
    assert(lista_notificare.get_all_notificari().size() == 9);

    lista_notificare.add_random_notificari(original_lista_notificare, 1);
    assert(lista_notificare.get_all_notificari().size() == 10);
}

void TestsListaNotificare::test_all_lista_notificare()
{
    test_add_notificare();
    test_empty_list();
    test_add_random_notificari();
}