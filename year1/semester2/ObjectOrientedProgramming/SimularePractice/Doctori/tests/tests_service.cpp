//
// Created by Alexandra on 5/17/2026.
//

#include <cassert>

#include "tests_service.h"

#include <iostream>

#include "../service/service_doctor.h"
#include "../utils/file_utils.h"

void TestsService::test_add()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    ServiceDoctor srv{repo};
    int n = (int)srv.get_all_doctori().size();
    srv.add_doctor("cnp11", "nume11", "prenume11", "sectie11", 1);
    assert(srv.get_all_doctori().size() == n + 1);
    try
    {
        srv.add_doctor("cnp11", "nume11", "prenume11", "sectie11", 1);
        assert(false);
    }
    catch (std::exception&)
    {
        assert(true);
    }
}

void TestsService::test_find()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    ServiceDoctor srv{repo};
    Doctor& doctor = srv.find_doctor("cnp1");
    assert(doctor.get_cnp() == "cnp1");
    assert(doctor.get_nume() == "nume1");
    assert(doctor.get_prenume() == "prenume1");
    assert(doctor.get_sectie() == "sectie1");
    assert(doctor.get_concediu() == 1);
    try
    {
        Doctor& d = srv.find_doctor("cnp11");
        assert(false);
    }
    catch (std::exception&)
    {
        assert(true);
    }
}

void TestsService::test_filter_by_nume()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    ServiceDoctor srv{repo};
    vector<Doctor> filtered_array = ServiceDoctor::filter_by_nume(srv.get_all_doctori(), "nume1");
    assert(filtered_array.size() == 1);
}

void TestsService::test_filter_by_sectie()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    ServiceDoctor srv{repo};
    vector<Doctor> filtered_array = ServiceDoctor::filter_by_sectie(srv.get_all_doctori(), "sectie1");
    assert(filtered_array.size() == 3);
}

void TestsService::test_all()
{
    test_add();
    test_find();
    test_filter_by_nume();
    test_filter_by_sectie();
}