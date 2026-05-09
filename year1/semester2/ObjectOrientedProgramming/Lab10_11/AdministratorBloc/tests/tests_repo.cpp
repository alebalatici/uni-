#include "tests_repo.h"
#include <filesystem>

void TestsRepo::test_add_locatar() {
    RepoLocatari repo;
    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};

    repo.add_locatar(l1);
    const auto& locatari = repo.get_all_locatari();
    assert(locatari.size() == 1);
    repo.add_locatar(l2);
    assert(locatari.size() == 2);
    repo.add_locatar(l3);
    assert(locatari.size() == 3);

    assert(locatari[0] == l1);
    assert(locatari[1] == l2);
    assert(locatari[2] == l3);

    assert(locatari[0].get_apartment() == 12324);
    assert(locatari[1].get_apartment() == 2343);
    assert(locatari[2].get_apartment() == 8765);

    assert(locatari[0].get_nume() == "A");
    assert(locatari[1].get_nume() == "Ab");
    assert(locatari[2].get_nume() == "Abc");

    assert(locatari[0].get_suprafata() == 1324.4);
    assert(locatari[1].get_suprafata() == 3454.4);
    assert(locatari[2].get_suprafata() == 6567.7);

    assert(locatari[0].get_tip() == "B");
    assert(locatari[1].get_tip() == "C");
    assert(locatari[2].get_tip() == "D");

    Locatar l4{12324, "Abcd", 34354.45, "E"};
    try {
        repo.add_locatar(l4);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void TestsRepo::test_get_all_locatari() {
    RepoLocatari repo;
    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    repo.add_locatar(l1);
    repo.add_locatar(l2);
    repo.add_locatar(l3);
    const auto& locatari = repo.get_all_locatari();
    assert(locatari.size() == 3);
}

void TestsRepo::test_delete_locatar() {
    RepoLocatari repo;
    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    repo.add_locatar(l1);
    repo.add_locatar(l2);
    repo.add_locatar(l3);
    const auto& locatari = repo.get_all_locatari();
    assert(locatari.size() == 3);
    repo.delete_locatar(12324);
    assert(locatari.size() == 2);
    repo.delete_locatar(2343);
    assert(locatari.size() == 1);
    assert(locatari[0].get_apartment() == 8765);
    try {
        repo.delete_locatar(12324);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void TestsRepo::test_find_locatar() {
    RepoLocatari repo;
    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    repo.add_locatar(l1);
    repo.add_locatar(l2);
    repo.add_locatar(l3);

    Locatar& loc1 = repo.find_locatar(12324);
    assert(loc1 == l1);
    assert(loc1.get_apartment() == 12324);
    assert(loc1.get_suprafata() == 1324.4);
    assert(loc1.get_tip() == "B");
    assert(loc1.get_nume() == "A");

    try {
        Locatar& loc2 = repo.find_locatar(1);
        (void)loc2;
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void TestsRepo::test_modify_locatar() {
    RepoLocatari repo;
    Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};
    repo.add_locatar(l1);
    repo.add_locatar(l2);
    repo.add_locatar(l3);

    Locatar &loc1 = repo.find_locatar(12324);
    assert(loc1 == l1);
    assert(loc1.get_apartment() == 12324);
    assert(loc1.get_suprafata() == 1324.4);
    assert(loc1.get_tip() == "B");
    assert(loc1.get_nume() == "A");
    repo.modify_locatar(12324, "B", 32456.56, "E");
    assert(loc1.get_apartment() == 12324);
    assert(loc1.get_suprafata() == 32456.56);
    assert(loc1.get_tip() == "E");
    assert(loc1.get_nume() == "B");
}

void TestsRepo::test_file_get_all_locatari()
{
    FileUtils::copy_template_to_target("data/test_locatari.txt", "data/default_locatari.txt");
    RepoLocatariFile repo("data/test_locatari.txt");
    assert(repo.get_all_locatari().size() == 15);

    try
    {
        RepoLocatariFile repo1("thisfiledoesnotexist.txt");
        assert(false);
    }
    catch (RepoException&)
    {
        assert(true);
    }

    try
    {
        RepoLocatariFile repo2("data/test_locatari_gresit.txt");
        assert(false);
    }
    catch (RepoException&)
    {
        assert(true);
    }
}

void TestsRepo::test_file_add_locatar()
{
    FileUtils::copy_template_to_target("data/test_locatari.txt", "data/default_locatari.txt");
    RepoLocatariFile repo("data/test_locatari.txt");

        Locatar l1{12324, "A", 1324.4, "B"};
    Locatar l2{2343, "Ab", 3454.4, "C"};
    Locatar l3{8765, "Abc", 6567.7, "D"};

    auto n = repo.get_all_locatari().size();
    repo.add_locatar(l1);
    const auto& locatari = repo.get_all_locatari();
    assert(locatari.size() == n + 1);
    repo.add_locatar(l2);
    assert(locatari.size() == n + 2);
    repo.add_locatar(l3);
    assert(locatari.size() == n + 3);

    assert(locatari[n] == l1);
    assert(locatari[n + 1] == l2);
    assert(locatari[n + 2] == l3);

    assert(locatari[n].get_apartment() == 12324);
    assert(locatari[n + 1].get_apartment() == 2343);
    assert(locatari[n + 2].get_apartment() == 8765);

    assert(locatari[n].get_nume() == "A");
    assert(locatari[n + 1].get_nume() == "Ab");
    assert(locatari[n + 2].get_nume() == "Abc");

    assert(locatari[n].get_suprafata() == 1324.4);
    assert(locatari[n + 1].get_suprafata() == 3454.4);
    assert(locatari[n + 2].get_suprafata() == 6567.7);

    assert(locatari[n].get_tip() == "B");
    assert(locatari[n + 1].get_tip() == "C");
    assert(locatari[n + 2].get_tip() == "D");
}

void TestsRepo::test_file_delete_locatar()
{
    FileUtils::copy_template_to_target("data/test_locatari.txt", "data/default_locatari.txt");
    RepoLocatariFile repo("data/test_locatari.txt");

    auto n = repo.get_all_locatari().size();
    repo.delete_locatar(1);
    assert(repo.get_all_locatari().size() == n - 1);
    repo.delete_locatar(2);
    assert(repo.get_all_locatari().size() == n - 2);
    repo.delete_locatar(3);
    assert(repo.get_all_locatari().size() == n - 3);
}

void TestsRepo::test_file_find_locatar()
{
    FileUtils::copy_template_to_target("data/test_locatari.txt", "data/default_locatari.txt");
    RepoLocatariFile repo("data/test_locatari.txt");

    Locatar l1{1, "Popescu Ion", 52.5, "apartament"};
    Locatar l2 = repo.find_locatar(1);

    assert(l1 == l2);
}

void TestsRepo::test_file_modify_locatar()
{
    FileUtils::copy_template_to_target("data/test_locatari.txt", "data/default_locatari.txt");
    RepoLocatariFile repo("data/test_locatari.txt");

    repo.modify_locatar(1, "B", 32456.56, "E");
    assert(repo.get_all_locatari()[0].get_nume() == "B");
    assert(repo.get_all_locatari()[0].get_suprafata() == 32456.56);
    assert(repo.get_all_locatari()[0].get_tip() == "E");
}

void TestsRepo::test_all_repo() {
    test_add_locatar();
    test_get_all_locatari();
    test_delete_locatar();
    test_find_locatar();
    test_modify_locatar();
    test_file_get_all_locatari();
    test_file_add_locatar();
    test_file_delete_locatar();
    test_file_find_locatar();
    test_file_modify_locatar();
}