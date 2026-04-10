#include "tests_domain.h"
#include <iostream>

void TestsDomain::test_get_domain() {
    Locatar l1{12324, "A", 1324.4, "B"};
    assert(l1.get_apartment() == 12324);
    assert(l1.get_nume() == "A");
    assert(l1.get_suprafata() == 1324.4);
    assert(l1.get_tip() == "B");

    Locatar l2{2343, "Ab", 3454.4, "C"};
    assert(l2.get_apartment() == 2343);
    assert(l2.get_nume() == "Ab");
    assert(l2.get_suprafata() == 3454.4);
    assert(l2.get_tip() == "C");

    Locatar l3{8765, "Abc", 6567.7, "D"};
    assert(l3.get_apartment() == 8765);
    assert(l3.get_nume() == "Abc");
    assert(l3.get_suprafata() == 6567.7);
    assert(l3.get_tip() == "D");
}
void TestsDomain::test_set_domain() {
    Locatar l{12324, "A", 1324.4, "B"};
    assert(l.get_apartment() == 12324);
    l.set_apartment(1);
    assert(l.get_apartment() == 1);
    assert(l.get_nume() == "A");
    l.set_nume("Ab");
    assert(l.get_nume() == "Ab");
    assert(l.get_suprafata() == 1324.4);
    l.set_suprafata(200.1324);
    assert(l.get_suprafata() == 200.1324);
    assert(l.get_tip() == "B");
    l.set_tip("C");
    assert(l.get_tip() == "C");
}

void TestsDomain::test_validator() {
    ValidatorLocatar val;
    Locatar l1{-1, "A", 453.53, "B"};
    try {
        val.validate(l1);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
    Locatar l2{12324, "", 1324.4, "B"};
    try {
        val.validate(l2);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
    Locatar l3{12324, "A", -324.54, "B"};
    try {
        val.validate(l3);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
    Locatar l4{12324, "A", 1324.4, ""};
    try {
        val.validate(l4);
        assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
    Locatar l5{12324, "A", 1324.4, "B"};
    try {
        val.validate(l5);
        assert(true);
    }
    catch (ValidationException&) {
        assert(false);
    }
}

void TestsDomain::test_all_domain() {
    test_get_domain();
    test_set_domain();
    test_validator();
}