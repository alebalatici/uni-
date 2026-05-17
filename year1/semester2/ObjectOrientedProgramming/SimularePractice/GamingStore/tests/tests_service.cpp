//
// Created by Alexandra on 5/16/2026.
//

#include <cassert>

#include "tests_service.h"
#include "../service/service_joc.h"
#include "../utils/file_utils.h"

void TestsService::test_add_srv()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    ServiceJoc srv{repo};
    int n = int(srv.get_all_jocuri().size());
    srv.add_joc("titlu11", 11.0, "PC", 12);
    assert(srv.get_all_jocuri().size() == n + 1);
    try
    {
        srv.add_joc("titlu11", 11.0, "PC", 12);
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

void TestsService::test_find_srv()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    ServiceJoc srv{repo};
    Joc& joc = srv.find_joc("titlu1");
    assert(joc.get_titlu() == "titlu1");
    assert(joc.get_pret() == 1.0);
    assert(joc.get_platforma() == "PC");
    assert(joc.get_age_rating() == 3);
    try
    {
        srv.find_joc("titlu11");
        assert(false);
    }
    catch (...)
    {
        assert(true);
    }
}

#include <iostream>
void TestsService::test_sort_by_price()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    ServiceJoc srv{repo};
    vector<Joc> sorted_array = ServiceJoc::sort_by_price_ascending(srv.get_all_jocuri());

    assert(sorted_array[0].get_titlu() == "titlu1");
    assert(sorted_array[9].get_titlu() == "titlu10");
}

void TestsService::test_filter_by_age_rating()
{
    FileUtils::copy_target_template("data/test_jocuri.txt", "data/default_jocuri.txt");
    RepoJocFile repo("data/test_jocuri.txt");
    ServiceJoc srv{repo};
    vector<Joc> filtered_array = ServiceJoc::filter_by_age_rating(srv.get_all_jocuri(), 5);

    std::cout << filtered_array.size() << std::endl;
    assert(filtered_array.size() == 3);
}

void TestsService::test_all_srv()
{
    test_add_srv();
    test_find_srv();
    test_sort_by_price();
    test_filter_by_age_rating();
}