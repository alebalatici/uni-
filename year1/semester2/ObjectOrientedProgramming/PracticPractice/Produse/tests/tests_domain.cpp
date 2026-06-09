//
// Created by Alexandra on 5/10/2026.
//

#include "tests_domain.h"

#include "../domain/validator.h"

void TestsDomain::test_get()
{
    Produs p1{1, "nume1", "tip1", 1.0};
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "nume1");
    assert(p1.get_tip() == "tip1");
    assert(p1.get_pret() == 1.0);
}

void TestsDomain::test_set()
{
    Produs p1{1, "nume1", "tip1", 1.0};
    assert(p1.get_id() == 1);
    assert(p1.get_nume() == "nume1");
    assert(p1.get_tip() == "tip1");
    assert(p1.get_pret() == 1.0);
    p1.set_nume("nume2");
    assert(p1.get_nume() == "nume2");
    p1.set_tip("tip2");
    assert(p1.get_tip() == "tip2");
    p1.set_pret(2.0);
    assert(p1.get_pret() == 2.0);
}

void TestsDomain::test_validator()
{
    Produs p1{1, "nume1", "tip1", 1.0};
    Validator val;
    try
    {
        val.validate(p1);
        assert(true);
    }
    catch (ValidationException&)
    {
        assert(false);
    }
    Produs p2{1, "", "tip1", 1.0};
    try
    {
        val.validate(p2);
        assert(false);
    }
    catch (ValidationException&)
    {
        assert(true);
    }
    Produs p3{1, "nume1", "tip1", 101.0};
    try
    {
        val.validate(p3);
        assert(false);
    }
    catch (ValidationException&)
    {
        assert(true);
    }
}

void TestsDomain::test_all_domain()
{
    test_get();
    test_set();
    test_validator();
}