//
// Created by Alexandra on 5/17/2026.
//

#include <cassert>

#include "tests_repo.h"
#include "../repo/repo_doctor.h"
#include "../utils/file_utils.h"

void TestsRepo::test_add()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    int n = (int)repo.get_all_doctori().size();
    repo.add_doctor(Doctor{"cnp11", "nume11", "prenume11", "sectie11", 1});
    assert(repo.get_all_doctori().size() == n + 1);

    try
    {
        repo.add_doctor(Doctor{"cnp11", "nume11", "prenume11", "sectie11", 1});
        assert(false);
    }
    catch (std::exception&)
    {
        assert(true);
    }
}

void TestsRepo::test_find()
{
    FileUtils::copy_target_template("data/test_doctori.txt", "data/default_doctori.txt");
    RepoDoctorFile repo("data/test_doctori.txt");
    Doctor& doctor = repo.find_doctor("cnp1");
    assert(doctor.get_cnp() == "cnp1");
    assert(doctor.get_nume() == "nume1");
    assert(doctor.get_prenume() == "prenume1");
    assert(doctor.get_sectie() == "sectie1");
    assert(doctor.get_concediu() == 1);
    try
    {
        Doctor& d = repo.find_doctor("cnp11");
        assert(false);
    }
    catch (std::exception&)
    {
        assert(true);
    }
}

void TestsRepo::test_all()
{
    test_add();
    test_find();
}