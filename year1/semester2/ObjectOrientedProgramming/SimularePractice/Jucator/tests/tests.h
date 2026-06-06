//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR_TESTS_H
#define JUCATOR_TESTS_H

#include "../repo/repo_jucatori.h"
#include "../service/service_jucatori.h"
#include <cassert>
#include <iostream>

class Tests {
private:
    static void test_add_repo()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        int n = (int)repo.get_all_jucatori().size();
        repo.add_jucator(Jucator{"nume11", "tara11", 11, 11});
        assert(repo.get_all_jucatori().size() == n + 1);
        try
        {
            repo.add_jucator(Jucator{"nume1", "tara11", 11, 11});
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void test_find_repo()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        Jucator& j = repo.find_jucator("nume1");
        assert(j.get_nume() == "nume1");
        assert(j.get_tara() == "tara1");
        assert(j.get_numar_puncte() == 1);
        assert(j.get_ranking() == 10);
        try
        {
            Jucator& jucator = repo.find_jucator("nume11");
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void test_delete_repo()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        int n = (int)repo.get_all_jucatori().size();
        repo.delete_jucator("nume1");
        assert(repo.get_all_jucatori().size() == n - 1);
        try
        {
            repo.delete_jucator("nume11");
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void test_add_srv()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        ServiceJucatori srv{repo};
        int n = (int)srv.get_all_jucatori().size();
        srv.add_jucator("nume11", "tara11", 11, 11);
        assert(srv.get_all_jucatori().size() == n + 1);
        try
        {
            srv.add_jucator("nume1", "tara11", 11, 11);
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void test_find_srv()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        ServiceJucatori srv{repo};
        Jucator& j = srv.find_jucator("nume1");
        assert(j.get_nume() == "nume1");
        assert(j.get_tara() == "tara1");
        assert(j.get_numar_puncte() == 1);
        assert(j.get_ranking() == 10);
        try
        {
            Jucator& jucator = srv.find_jucator("nume11");
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

    static void test_delete_srv()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        ServiceJucatori srv{repo};
        int n = (int)srv.get_all_jucatori().size();
        srv.delete_jucator("nume1");
        assert(srv.get_all_jucatori().size() == n - 1);
        try
        {
            srv.delete_jucator("nume11");
            assert(false);
        }
        catch (std::exception&)
        {
            assert(true);
        }
    }

public:
    static void test_all()
    {
        test_add_repo();
        test_find_repo();
        test_delete_repo();

        test_add_srv();
        test_find_srv();
        test_delete_srv();
    }
};



#endif //JUCATOR_TESTS_H
