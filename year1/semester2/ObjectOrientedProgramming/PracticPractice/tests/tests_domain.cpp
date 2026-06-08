//
// Created by Alexandra on 5/9/2026.
//

#include <exception>
#include "tests_domain.h"
void TestsDomain::test_get_domain()
{
    Melodie m{1, "titlu1", "artist1", 10};
    assert(m.get_id() == 1);
    assert(m.get_titlu() == "titlu1");
    assert(m.get_artist() == "artist1");
    assert(m.get_rank() == 10);
}

void TestsDomain::test_set_domain()
{
    Melodie m{1, "titlu1", "artist1", 10};
    assert(m.get_id() == 1);
    assert(m.get_titlu() == "titlu1");
    assert(m.get_artist() == "artist1");
    assert(m.get_rank() == 10);
    m.set_titlu("titlu2");
    m.set_artist("artist2");
    m.set_rank(9);
    assert(m.get_titlu() == "titlu2");
    assert(m.get_artist() == "artist2");
    assert(m.get_rank() == 9);
}

void TestsDomain::test_validator()
{
    Melodie m1{1, "titlu1", "artist1", 10};
    Validator val;
    try
    {
        val.validate(m1);
        assert(true);
    }
    catch(ValidationException& e)
    {
        assert(false);
    }
    Melodie m2{-1, "titlu1", "artist1", 10};
    try
    {
        val.validate(m2);
        assert(false);
    }
    catch(ValidationException& e)
    {
        assert(true);
    }
    Melodie m3{1, "", "artist1", 10};
    try
    {
        val.validate(m3);
        assert(false);
    }
    catch(ValidationException& e)
    {
        assert(true);
    }
    Melodie m4{1, "titlu1", "", 10};
    try
    {
        val.validate(m4);
        assert(false);
    }
    catch(ValidationException& e)
    {
        assert(true);
    }
    Melodie m5{1, "titlu1", "artist1", 20};
    try
    {
        val.validate(m5);
        assert(false);
    }
    catch(ValidationException& e)
    {
        assert(true);
    }
}

void TestsDomain::test_all_domain()
{
    test_get_domain();
    test_set_domain();
    test_validator();
}