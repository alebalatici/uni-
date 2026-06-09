//
// Created by Alexandra on 5/10/2026.
//

#include "tests_service.h"

void TestsService::test_add_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};
    int n = int(srv.get_all_produse().size());
    srv.add_produs(n + 1, "nume1", "tip1", 1.0);
    assert(srv.get_all_produse().size() == n + 1);
}

void TestsService::test_delete_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};
    int n = int(srv.get_all_produse().size());
    srv.delete_produs(1);
    assert(srv.get_all_produse().size() == n - 1);
}

void TestsService::test_modify_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};

    Produs& p1 = srv.find_produs(1);
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "Laptop ASUS");
    assert(p1.get_tip() == "Electronice");
    assert(p1.get_pret() == 3499.99);
    srv.modify_produs(1, "nume2", "tip2", 2.0);
    Produs& p2 = srv.find_produs(1);
    assert(p2.get_id() == 1);
    assert(p2.get_nume() == "nume2");
    assert(p2.get_tip() == "tip2");
    assert(p2.get_pret() == 2.0);
}

void TestsService::test_find_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};
    Produs& p = srv.find_produs(1);
    assert(p.get_id() == 1);
    assert(p.get_nume() == "Laptop ASUS");
    assert(p.get_tip() == "Electronice");
    assert(p.get_pret() == 3499.99);
}

void TestsService::test_sort_by_price()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Validator val;
    ServiceProdus srv{repo, val};
    vector<Produs> sorted = ServiceProdus::sort_by_price(srv.get_all_produse());
    assert(sorted.size() == 10);
    assert(sorted[0].get_nume() == "Mouse Gaming");
    assert(sorted[9].get_nume() == "Telefon iPhone 15");
}

void TestsService::test_all_service()
{
    test_add_produs();
    test_delete_produs();
    test_modify_produs();
    test_find_produs();
    test_sort_by_price();
}