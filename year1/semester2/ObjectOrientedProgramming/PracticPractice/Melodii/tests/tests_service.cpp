//
// Created by Alexandra on 5/9/2026.
//

#include "tests_service.h"

void TestsService::test_add_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    Validator val;
    ServiceMelodii srv{repo, val};
    int n = int(srv.get_all_melodii().size());
    assert(n == 10);
    srv.add_melodie(n + 1, "titlu", "artist", 10);
    assert(srv.get_all_melodii().empty() == false);
    assert(srv.get_all_melodii().size() == n + 1);
}

void TestsService::test_delete_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    Validator val;
    ServiceMelodii srv{repo, val};
    int n = int(srv.get_all_melodii().size());
    assert(n == 10);
    srv.delete_melodie(1);
    assert(srv.get_all_melodii().empty() == false);
    assert(srv.get_all_melodii().size() == n - 1);
}

void TestsService::test_modify_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    Validator val;
    ServiceMelodii srv{repo, val};
    srv.modify_melodie(1,  "titlu1", "artist1", 9);
    Melodie &melodie = srv.find_melodie(1);
    assert(melodie.get_titlu() == "titlu1");
    assert(melodie.get_artist() == "artist1");
    assert(melodie.get_rank() == 9);
}

void TestsService::test_find_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    Validator val;
    ServiceMelodii srv{repo, val};
    Melodie &melodie = srv.find_melodie(1);
    assert(melodie.get_titlu() == "Bohemian Rhapsody");
    assert(melodie.get_artist() == "Queen");
    assert(melodie.get_rank() == 10);
}

void TestsService::test_all_service()
{
    test_add_melodie();
    test_delete_melodie();
    test_modify_melodie();
    test_find_melodie();
}