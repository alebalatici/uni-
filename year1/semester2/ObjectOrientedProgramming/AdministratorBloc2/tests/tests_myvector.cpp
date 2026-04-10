#include "tests_myvector.h"

void TestsMyVector::
test_resize_push_back_size_capacity_empty()
{
    MyVector<int> numere;
    assert(numere.empty() == true);
    numere.push_back(1);
    assert(numere.empty() == false);
    assert(numere.size() == 1);
    assert(numere.capacity() == 1);
    numere.push_back(2);
    assert(numere.size() == 2);
    assert(numere.capacity() == 2);
    numere.push_back(3);
    assert(numere.size() == 3);
    assert(numere.capacity() == 4);
    assert(numere.empty() == false);

    MyVector<Locatar> locatari;
    assert(locatari.empty() == true);
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});
    assert(locatari.size() == 3);
    assert(locatari.capacity() == 4);
    assert(locatari.empty() == false);

    MyVector<bool> boolvector;
    assert(boolvector.empty() == true);
    boolvector.push_back(true);
    boolvector.push_back(false);
    boolvector.push_back(false);
    boolvector.push_back(false);
    assert(boolvector.empty() == false);
    boolvector.push_back(true);
    boolvector.push_back(false);
    assert(boolvector.empty() == false);
    boolvector.push_back(false);
    assert(boolvector.size() == 7);
    assert(boolvector.capacity() == 8);
    assert(boolvector.empty() == false);
}

void TestsMyVector::test_at()
{
    MyVector<Locatar> locatari;
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});

    Locatar l1{1,"Ana", 34.34, "ABC"};
    Locatar l2{2,"Ana", 34.34, "ABC"};
    Locatar l3{3,"Ana", 34.34, "ABC"};
    assert(locatari.at(0) == l1);
    assert(locatari.at(1) == l2);
    assert(locatari.at(2) == l3);

    try
    {
        Locatar l = locatari.at(11);
        assert(false);
    }
    catch (std::out_of_range)
    {
        assert(true);
    }
}

void TestsMyVector::test_operator()
{
    MyVector<Locatar> locatari;
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});

    Locatar l1{1,"Ana", 34.34, "ABC"};
    Locatar l2{2,"Ana", 34.34, "ABC"};
    Locatar l3{3,"Ana", 34.34, "ABC"};

    assert(locatari[0] == l1);
    assert(locatari[1] == l2);
    assert(locatari[2] == l3);
}

void TestsMyVector::test_begin_end()
{
    MyVector<Locatar> locatari;
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});
    assert(locatari.begin() == &locatari[0]);
    assert(locatari.end() == &locatari[2] + (&locatari[1] - &locatari[0]));
    assert(locatari.end() == locatari.begin() + locatari.size());
}

void TestsMyVector::test_erase()
{
    MyVector<Locatar> locatari;
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});

    auto it = locatari.begin();
    while(it != locatari.end())
        if (it->get_apartment() == 1)
            locatari.erase(it);
        else it++;

    assert(locatari.size() == 2);
    assert(locatari.capacity() == 4);
    assert(locatari.empty() == false);
    assert(locatari.at(0).get_apartment() == 2);
    assert(locatari.at(1).get_apartment() == 3);

}

void TestsMyVector::test_copy_and_equal()
{
    MyVector<Locatar> locatari;
    locatari.push_back(Locatar{1,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari.push_back(Locatar{3,"Ana", 34.34, "ABC"});

    MyVector<Locatar> locatari_copie = locatari;
    assert(locatari == locatari_copie);

    MyVector<Locatar> locatari1;
    locatari1.push_back(Locatar{2,"Ana", 34.34, "ABC"});
    locatari1.push_back(Locatar{3,"Ana", 34.34, "ABC"});
    assert(locatari1 == locatari == false);
    locatari1.push_back(Locatar{4,"Ana", 34.34, "ABC"});
    assert(locatari1 == locatari == false);
}

void TestsMyVector::test_all_myvector()
{
    test_resize_push_back_size_capacity_empty();
    test_at();
    test_operator();
    test_begin_end();
    test_erase();
    test_copy_and_equal();
}