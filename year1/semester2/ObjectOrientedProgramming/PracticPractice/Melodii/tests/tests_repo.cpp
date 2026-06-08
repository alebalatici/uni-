//
// Created by Alexandra on 5/9/2026.
//

#include "tests_repo.h"
void TestsRepo::test_add_melodie()
{
    RepoMelodii repo;
    assert(repo.get_all_melodii().empty() == true);
    Melodie m{1, "titlu", "artist", 10};
    repo.add_melodie(m);
    assert(repo.get_all_melodii().empty() == false);
    assert(repo.get_all_melodii().size() == 1);
}

void TestsRepo::test_delete_melodie()
{
    RepoMelodii repo;
    assert(repo.get_all_melodii().empty() == true);
    Melodie m{1, "titlu", "artist", 10};
    repo.add_melodie(m);
    assert(repo.get_all_melodii().empty() == false);
    assert(repo.get_all_melodii().size() == 1);
    repo.delete_melodie(1);
    assert(repo.get_all_melodii().empty() == true);
}

void TestsRepo::test_modify_melodie()
{
    RepoMelodii repo;
    assert(repo.get_all_melodii().empty() == true);
    Melodie m{1, "titlu", "artist", 10};
    repo.add_melodie(m);
    assert(repo.get_all_melodii().empty() == false);
    assert(repo.get_all_melodii().size() == 1);
    repo.modify_melodie(1, "titlu1", "artist1", 9);
    Melodie &melodie = repo.find_melodie(1);
    assert(melodie.get_titlu() == "titlu1");
    assert(melodie.get_artist() == "artist1");
    assert(melodie.get_rank() == 9);
}

void TestsRepo::test_find_melodie()
{
    RepoMelodii repo;
    assert(repo.get_all_melodii().empty() == true);
    Melodie m{1, "titlu", "artist", 10};
    repo.add_melodie(m);
    Melodie& melodie = repo.find_melodie(1);
    assert(m == melodie);
}

void TestsRepo::test_file_add_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    int n = int(repo.get_all_melodii().size());
    assert(n == 10);
    Melodie m{n + 1, "titlu", "artist", 10};
    repo.add_melodie(m);
    assert(repo.get_all_melodii().empty() == false);
    assert(repo.get_all_melodii().size() == n + 1);
}

void TestsRepo::test_file_delete_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    int n = int(repo.get_all_melodii().size());
    repo.delete_melodie(1);
    assert(repo.get_all_melodii().size() == n - 1);
}

void TestsRepo::test_file_modify_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    repo.modify_melodie(1,  "titlu1", "artist1", 9);
    Melodie &melodie = repo.find_melodie(1);
    assert(melodie.get_titlu() == "titlu1");
    assert(melodie.get_artist() == "artist1");
    assert(melodie.get_rank() == 9);
}

void TestsRepo::test_file_find_melodie()
{
    FileUtils::copy_target_template("data/test_melodii.txt", "data/default_melodii.txt");
    RepoMelodiiFile repo("data/test_melodii.txt");
    Melodie &melodie = repo.find_melodie(1);
    assert(melodie.get_titlu() == "Bohemian Rhapsody");
    assert(melodie.get_artist() == "Queen");
    assert(melodie.get_rank() == 10);
}

void TestsRepo::test_all_repo()
{
    test_add_melodie();
    test_delete_melodie();
    test_modify_melodie();
    test_find_melodie();

    test_file_add_melodie();
    test_file_delete_melodie();
    test_file_modify_melodie();
    test_file_find_melodie();
}