//
// Created by Alexandra on 5/16/2026.
//

#include <cassert>
#include "tests_repo.h"
#include "../repo/repo_joc.h"
#include "../utils/file_utils.h"

void TestsRepo::test_add_joc()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    int n = int(repo.get_all_jocuri().size());
    repo.add_joc(Joc{"titlu11", 11.0, "XBOX", 12});
    assert(repo.get_all_jocuri().size() == n + 1);
    try
    {
        repo.add_joc(Joc{"titlu11", 11.0, "XBOX", 12});
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void TestsRepo::test_find_joc()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    Joc& joc = repo.find_joc("titlu1");
    assert(joc.get_titlu() == "titlu1");
    assert(joc.get_pret() == 1.0);
    assert(joc.get_platforma() == "PC");
    assert(joc.get_age_rating() == 3);
    try
    {
        repo.find_joc("titlu11");
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void TestsRepo::test_all_repo()
{
    test_add_joc();
    test_find_joc();
}