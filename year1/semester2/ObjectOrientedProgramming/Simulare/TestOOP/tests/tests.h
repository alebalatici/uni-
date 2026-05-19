//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_TESTS_H
#define TESTOOP_TESTS_H

#include <cassert>
#include <iostream>

#include "../repo/repo_radiation.h"
#include "../domain/validator.h"
#include "../service/service_radiation.h"
class Tests {
    private:
    static void test_add_repo()
    {
        RepoRadiationFile repo("data/test_radiatii.txt");
        int n = (int)repo.get_all_radiatii().size();
        repo.add_radiation(Radiation{11, "descriere1", 1.0, "tip11"});
        assert(repo.get_all_radiatii().size() == n + 1);
        assert(repo.get_all_radiatii().size() == 11);
    }

    static void test_add_service()
    {
        RepoRadiationFile repo("data/test_radiatii.txt");
        Validator val;
        ServiceRadiation srv{repo, val};
        int n = (int)srv.get_all_radiatii().size();
        srv.add_radiation(11, "descriere1", 1.0, "alpha");
        assert(srv.get_all_radiatii().size() == n + 1);
        assert(srv.get_all_radiatii().size() == 11);

        try
        {
            srv.add_radiation(11, "", 1.0, "alpha");
            assert(false);
        }
        catch(...)
        {
            assert(true);
        }

        try
        {
            srv.add_radiation(11, "descriere", 1000.0, "alpha");
            assert(false);
        }
        catch(...)
        {
            assert(true);
        }

        try
        {
            srv.add_radiation(11, "d", 1.0, "tip");
            assert(false);
        }
        catch(...)
        {
            assert(true);
        }
    }

    static void test_filtrare_frecventa()
    {
        RepoRadiationFile repo("data/test_radiatii.txt");
        Validator val;
        ServiceRadiation srv{repo, val};
        vector<Radiation> filtered = ServiceRadiation::filtrare_frecventa(srv.get_all_radiatii(), 5);
        assert(filtered.size() == 5);
    }

    static void test_filtrare_string()
    {
        RepoRadiationFile repo("data/test_radiatii.txt");
        Validator val;
        ServiceRadiation srv{repo, val};
        vector<Radiation> filtered = ServiceRadiation::filtrare_string(srv.get_all_radiatii(), "alpha");
        assert(filtered.size() == 5);
    }

    public:
    static void test_all()
    {
        test_add_repo();
        test_add_service();
        test_filtrare_frecventa();
    }

};



#endif //TESTOOP_TESTS_H
