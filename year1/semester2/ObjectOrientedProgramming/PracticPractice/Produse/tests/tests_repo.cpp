//
// Created by Alexandra on 5/10/2026.
//

#include "tests_repo.h"

#include <iostream>

void TestsRepo::test_add_produs()
{
    RepoProdus repo;
    Produs p1{1, "nume1", "tip1", 1.0};
    assert(repo.get_all_produse().empty() == true);
    repo.add_produs(p1);
    assert(repo.get_all_produse().size() == 1);
    assert(repo.get_all_produse().empty() == false);
    try
    {
        repo.add_produs(p1);
        assert(false);
    }
    catch (RepoException&)
    {
        assert(true);
    }
}

void TestsRepo::test_delete_produs()
{
    RepoProdus repo;
    Produs p1{1, "nume1", "tip1", 1.0};
    assert(repo.get_all_produse().empty() == true);
    repo.add_produs(p1);
    assert(repo.get_all_produse().size() == 1);
    assert(repo.get_all_produse().empty() == false);
    repo.delete_produs(1);
    assert(repo.get_all_produse().empty() == true);

    try
    {
        repo.delete_produs(1);
        assert(false);
    }
    catch (RepoException&)
    {
        assert(true);
    }
}

void TestsRepo::test_modify_produs()
{
    RepoProdus repo;
    Produs p{1, "nume1", "tip1", 1.0};
    repo.add_produs(p);
    Produs& p1 = repo.find_produs(1);
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "nume1");
    assert(p1.get_tip() == "tip1");
    assert(p1.get_pret() == 1.0);
    repo.modify_produs(1, "nume2", "tip2", 2.0);
    Produs& p2 = repo.find_produs(1);
    assert(p2.get_id() == 1);
    assert(p2.get_nume() == "nume2");
    assert(p2.get_tip() == "tip2");
    assert(p2.get_pret() == 2.0);
}

void TestsRepo::test_find_produs()
{
    RepoProdus repo;
    Produs p{1, "nume1", "tip1", 1.0};
    repo.add_produs(p);
    Produs& p1 = repo.find_produs(1);
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "nume1");
    assert(p1.get_tip() == "tip1");
    assert(p1.get_pret() == 1.0);
}

void TestsRepo::test_file_add_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    int n = int(repo.get_all_produse().size());
    Produs p1{n + 1, "nume1", "tip1", 1.0};
    repo.add_produs(p1);
    assert(repo.get_all_produse().size() == n + 1);
}

void TestsRepo::test_file_delete_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    int n = int(repo.get_all_produse().size());
    repo.delete_produs(1);
    assert(repo.get_all_produse().size() == n - 1);
}

void TestsRepo::test_file_modify_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Produs& p1 = repo.find_produs(1);
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "Laptop ASUS");
    assert(p1.get_tip() == "Electronice");
    assert(p1.get_pret() == 3499.99);
    repo.modify_produs(1, "nume2", "tip2", 2.0);
    Produs& p2 = repo.find_produs(1);
    assert(p2.get_id() == 1);
    assert(p2.get_nume() == "nume2");
    assert(p2.get_tip() == "tip2");
    assert(p2.get_pret() == 2.0);
}

void TestsRepo::test_file_find_produs()
{
    FileUtils::copy_target_template("data/default_produse.txt", "data/test_produse.txt");
    RepoProdusFile repo("data/test_produse.txt");
    Produs& p = repo.find_produs(1);
    assert(p.get_id() == 1);
    assert(p.get_nume() == "Laptop ASUS");
    assert(p.get_tip() == "Electronice");
    assert(p.get_pret() == 3499.99);
}

void TestsRepo::test_all_repo()
{
    test_add_produs();
    test_delete_produs();
    test_modify_produs();
    test_find_produs();

    test_file_add_produs();
    test_file_delete_produs();
    test_file_modify_produs();
    test_file_find_produs();
}