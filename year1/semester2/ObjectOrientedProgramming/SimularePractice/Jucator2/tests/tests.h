//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR2_TESTS_H
#define JUCATOR2_TESTS_H

#include <cassert>
#include <iostream>
#include <qtextstream.h>

#include "../service/service_jucatori.h"

class Tests {
private:
    static void test_add_repo()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        int n = (int)repo.get_all_jucatori().size();
        repo.add_jucator(Jucator{"nume11", "tara11", 0, 11});
        assert(repo.get_all_jucatori().size() == n + 1);
        assert(repo.get_all_jucatori().size() == 11);
    }

    static void test_add_srv()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        ServiceJucatori srv{repo};
        int n = (int)srv.get_all_jucatori().size();
        srv.add_jucator("nume11", "tara11", 0, 11);
        assert(srv.get_all_jucatori().size() == n + 1);
        assert(srv.get_all_jucatori().size() == 11);
    }

    static void test_get_coutries()
    {
        RepoJucatoriFile repo("data/test_jucatori.txt");
        ServiceJucatori srv{repo};
        vector<string> coutries = ServiceJucatori::get_all_countries(srv.get_all_jucatori());
        assert(coutries.size() == 4);
    }

public:
    static void test_all()
    {
        test_add_repo();
        test_add_srv();
        test_get_coutries();
    }
};

#endif //JUCATOR2_TESTS_H
