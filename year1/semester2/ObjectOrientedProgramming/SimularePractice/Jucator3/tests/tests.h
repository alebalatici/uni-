//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR3_TESTS_H
#define JUCATOR3_TESTS_H

#include <cassert>
#include "../service/service_jucator.h"

class Tests {
private:
    static void test_add_repo()
    {
        RepoJucatorFile repo("data/test_jucatori.txt");
        int n = (int)repo.get_all_jucatori().size();
        repo.add_jucator(Jucator{"nume11", "tara11", 11, 11});
        assert(repo.get_all_jucatori().size() == n + 1);
    }
    static void test_add_serivce()
    {
        RepoJucatorFile repo("data/test_jucatori.txt");
        ServiceJucator srv{repo};
        int n = (int)srv.get_all_jucatori().size();
        srv.add_jucator("nume11", "tara11", 11, 11);
        assert(srv.get_all_jucatori().size() == n + 1);
    }

public:
    static void test_all()
    {
        test_add_repo();
        test_add_serivce();
    }
};

#endif //JUCATOR3_TESTS_H
