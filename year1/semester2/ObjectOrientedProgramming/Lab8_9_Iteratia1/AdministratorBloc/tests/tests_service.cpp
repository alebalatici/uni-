#include "tests_service.h"

void TestsService::test_add_locatar() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    const auto &locatari = srv.get_all_locatari();
    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    assert(locatari.size() == 1);
    assert(locatari[0].get_nume() == "Ion");
    assert(locatari[0].get_apartment() == 1);
    assert(locatari[0].get_suprafata() == 50.5);
    assert(locatari[0].get_tip() == "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    assert(locatari.size() == 2);
    assert(locatari[1].get_nume() == "Lavinia");
    assert(locatari[1].get_apartment() == 2);
    assert(locatari[1].get_suprafata() == 60.4);
    assert(locatari[1].get_tip() == "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    assert(locatari.size() == 3);
    assert(locatari[2].get_nume() == "Florin");
    assert(locatari[2].get_apartment() == 3);
    assert(locatari[2].get_suprafata() == 533.0);
    assert(locatari[2].get_tip() == "garsoniera");

    try {
        srv.add_locatar(1, "Laurentiu", 54.54, "garsoniera");
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
    try {
        srv.add_locatar(-1, "Laurentiu", 54.54, "garsoniera");
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
}
void TestsService::test_get_all_locatari() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    const auto &locatari = srv.get_all_locatari();
    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    assert(locatari.size() == 1);
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    assert(locatari.size() == 2);
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    assert(locatari.size() == 3);
}
void TestsService::test_delete_locatar() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    const auto &locatari = srv.get_all_locatari();
    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    assert(locatari.size() == 1);
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    assert(locatari.size() == 2);
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    assert(locatari.size() == 3);
    srv.delete_locatar(2);
    assert(locatari.size() == 2);
    srv.delete_locatar(1);
    assert(locatari.size() == 1);
    try {
        srv.delete_locatar(4);
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
}

void TestsService::test_find_locatar() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");

    Locatar& l = srv.find_locatar(2);
    Locatar l1{2, "Lavinia", 60.4, "apartament"};
    assert(l == l1);

    try {
        srv.find_locatar(4);
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
}

void TestsService::test_modify_locatar() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");

    const auto &locatari = srv.get_all_locatari();
    assert(locatari.size() == 3);
    assert(locatari[0].get_nume() == "Ion");
    assert(locatari[0].get_apartment() == 1);
    assert(locatari[0].get_suprafata() == 50.5);
    assert(locatari[0].get_tip() == "penthouse");
    srv.modify_locatar(1, "Ion Popescu", 543.56, "apartament");
    assert(locatari.size() == 3);
    assert(locatari[0].get_nume() == "Ion Popescu");
    assert(locatari[0].get_apartment() == 1);
    assert(locatari[0].get_suprafata() == 543.56);
    assert(locatari[0].get_tip() == "apartament");

    try {
        srv.modify_locatar(4, "Popescu", 533.56, "garsoniera");
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
    try {
        srv.modify_locatar(1, "", 4390.4, "garsoniera");
        assert(false);
    }
    catch (ServiceException&) {
        assert(true);
    }
}

void TestsService:: test_count_vowels() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    assert(srv.count_vowels("plant") == 1);
    assert(srv.count_vowels("basin") == 2);
    assert(srv.count_vowels("proud") == 2);
    assert(srv.count_vowels("matrix") == 2);
    assert(srv.count_vowels("hide") == 2);
    assert(srv.count_vowels("payment") == 2);
    assert(srv.count_vowels("queue") == 4);
    assert(srv.count_vowels("hover") == 2);
    assert(srv.count_vowels("linen") == 2);
    assert(srv.count_vowels("medieval") == 4);
}

void TestsService::test_filter_after_type() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    srv.add_locatar(4, "Ion", 3590, "penthouse");
    srv.add_locatar(5, "Lavinia", 60.4, "apartament");
    srv.add_locatar(6, "Florin", 35490.0, "penthouse");
    srv.add_locatar(7, "Ion", 50.5, "penthouse");
    srv.add_locatar(8, "Lavinia", 4096.4, "penthouse");
    srv.add_locatar(9, "Florin", 690.0, "garsoniera");


    vector<Locatar> filtered_list = ServiceLocatari::filter_after_type(srv.get_all_locatari(), "penthouse");
    assert(filtered_list.size() == 5);
}

void TestsService::test_filter_after_surface() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    srv.add_locatar(4, "Ion", 3590, "penthouse");
    srv.add_locatar(5, "Lavinia", 60.4, "apartament");
    srv.add_locatar(6, "Florin", 35490.0, "penthouse");
    srv.add_locatar(7, "Ion", 50.5, "penthouse");
    srv.add_locatar(8, "Lavinia", 4096.4, "penthouse");
    srv.add_locatar(9, "Florin", 690.0, "garsoniera");

    vector<Locatar> fitered_list = ServiceLocatari::filter_after_surface(srv.get_all_locatari(), 100);
    assert(fitered_list.size() == 5);
}

void TestsService::test_sort_after_name() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(54, "Florin", 50.5, "penthouse");
    srv.add_locatar(33, "Gabriela", 60.4, "apartament");
    srv.add_locatar(78, "Oana", 533.0, "garsoniera");
    srv.add_locatar(43, "Paula", 3590, "penthouse");
    srv.add_locatar(567, "Radu", 60.4, "apartament");
    srv.add_locatar(3, "Sorina", 35490.0, "penthouse");
    srv.add_locatar(76, "Xenia", 50.5, "penthouse");

    vector<Locatar>sorted_list = ServiceLocatari::sort_after_name(srv.get_all_locatari());
    assert(sorted_list.size() == 7);
    assert(sorted_list[0].get_nume() == "Florin");
    assert(sorted_list[1].get_nume() == "Gabriela");
    assert(sorted_list[2].get_nume() == "Oana");
    assert(sorted_list[3].get_nume() == "Paula");
    assert(sorted_list[4].get_nume() == "Radu");
    assert(sorted_list[5].get_nume() == "Sorina");
    assert(sorted_list[6].get_nume() == "Xenia");
}

void TestsService::test_sort_after_surface() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(54, "Florin", 434.34, "penthouse");
    srv.add_locatar(33, "Gabriela", 60.4, "apartament");
    srv.add_locatar(78, "Oana", 56, "garsoniera");
    srv.add_locatar(43, "Paula", 45.6, "penthouse");
    srv.add_locatar(567, "Radu", 4.2, "apartament");
    srv.add_locatar(3, "Sorina", 1.2, "penthouse");
    srv.add_locatar(76, "Xenia", 6767.6, "penthouse");
    srv.add_locatar(56, "Florin", 334.3, "penthouse");
    srv.add_locatar(67, "Gabriela", 354, "apartament");

    vector<Locatar>sorted_list = ServiceLocatari::sort_after_surface(srv.get_all_locatari());
    assert(sorted_list.size() == 9);
    assert(sorted_list[0].get_suprafata() == 1.2);
    assert(sorted_list[1].get_suprafata() == 4.2);
    assert(sorted_list[2].get_suprafata() == 45.6);
    assert(sorted_list[3].get_suprafata() == 56);
    assert(sorted_list[4].get_suprafata() == 60.4);
    assert(sorted_list[5].get_suprafata() == 334.3);
    assert(sorted_list[6].get_suprafata() == 354);
    assert(sorted_list[7].get_suprafata() == 434.34);
    assert(sorted_list[8].get_suprafata() == 6767.6);
}

void TestsService::test_sort_after_type_and_surface() {
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(54, "Florin", 434.34, "penthouse");
    srv.add_locatar(33, "Gabriela", 60.4, "penthouse");
    srv.add_locatar(78, "Oana", 56, "penthouse");

    srv.add_locatar(43, "Paula", 45.6, "apartament");
    srv.add_locatar(567, "Radu", 4.2, "apartament");
    srv.add_locatar(3, "Sorina", 1.2, "apartament");

    srv.add_locatar(76, "Xenia", 6767.6, "garsoniera");
    srv.add_locatar(56, "Florin", 334.3, "garsoniera");
    srv.add_locatar(67, "Gabriela", 354, "garsoniera");

    vector<Locatar>sorted_list = ServiceLocatari::sort_after_type_and_surface(srv.get_all_locatari());
    assert(sorted_list[0].get_tip() == "apartament");
    assert(sorted_list[0].get_suprafata() == 1.2);
    assert(sorted_list[1].get_tip() == "apartament");
    assert(sorted_list[1].get_suprafata() == 4.2);
    assert(sorted_list[2].get_tip() == "apartament");
    assert(sorted_list[2].get_suprafata() == 45.6);

    assert(sorted_list[3].get_tip() == "garsoniera");
    assert(sorted_list[3].get_suprafata() == 334.3);
    assert(sorted_list[4].get_tip() == "garsoniera");
    assert(sorted_list[4].get_suprafata() == 354);
    assert(sorted_list[5].get_tip() == "garsoniera");
    assert(sorted_list[5].get_suprafata() == 6767.6);

    assert(sorted_list[6].get_tip() == "penthouse");
    assert(sorted_list[6].get_suprafata() == 56);
    assert(sorted_list[7].get_tip() == "penthouse");
    assert(sorted_list[7].get_suprafata() == 60.4);
    assert(sorted_list[8].get_tip() == "penthouse");
    assert(sorted_list[8].get_suprafata() == 434.34);
}

void TestsService::test_list_add_notificare()
{
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");

    assert(srv.list_get_all_notificari().empty() == true);
    srv.list_add_notificare(1);
    assert(srv.list_get_all_notificari().size() == 1);
    assert(srv.list_get_all_notificari()[0].get_nume() == "Ion");
    assert(srv.list_get_all_notificari()[0].get_suprafata() == 50.5);
    assert(srv.list_get_all_notificari()[0].get_tip() == "penthouse");

    srv.list_add_notificare(2);
    assert(srv.list_get_all_notificari().size() == 2);
    assert(srv.list_get_all_notificari()[1].get_nume() == "Lavinia");
    assert(srv.list_get_all_notificari()[1].get_suprafata() == 60.4);
    assert(srv.list_get_all_notificari()[1].get_tip() == "apartament");

    srv.list_add_notificare(3);
    assert(srv.list_get_all_notificari().size() == 3);
    assert(srv.list_get_all_notificari()[2].get_nume() == "Florin");
    assert(srv.list_get_all_notificari()[2].get_suprafata() == 533.0);
    assert(srv.list_get_all_notificari()[2].get_tip() == "garsoniera");
}

void TestsService::test_list_empty_full()
{
    RepoLocatari repo;
    ValidatorLocatar val;
    ServiceLocatari srv{repo, val};

    srv.add_locatar(1, "Ion", 50.5, "penthouse");
    srv.add_locatar(2, "Lavinia", 60.4, "apartament");
    srv.add_locatar(3, "Florin", 533.0, "garsoniera");
    assert(srv.list_get_all_notificari().empty() == true);

    srv.list_add_notificare(1);
    srv.list_add_notificare(2);
    srv.list_add_notificare(3);
    assert(srv.list_get_all_notificari().empty() == false);
    assert(srv.list_get_all_notificari().size() == 3);

    srv.list_empty_full();
    assert(srv.list_get_all_notificari().empty() == true);
}

void TestsService::test_all_service() {
    test_add_locatar();
    test_get_all_locatari();
    test_delete_locatar();
    test_find_locatar();
    test_modify_locatar();
    test_count_vowels();
    test_filter_after_type();
    test_filter_after_surface();
    test_sort_after_name();
    test_sort_after_surface();
    test_sort_after_type_and_surface();
    test_list_add_notificare();
    test_list_empty_full();
    test_list_add_random_notificari();
}

void TestsService::test_list_add_random_notificari()
{

}