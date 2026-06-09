//
// Created by Alexandra on 5/10/2026.
//

#include <algorithm>
#include "service_produs.h"
using std::sort;
void ServiceProdus::add_produs(int id, const string& nume, const string& tip, double pret)
{
    try
    {
        Produs produs{id, nume, tip, pret};
        val.validate(produs);
        repo.add_produs(produs);
        notify();
    }
    catch(exception& e)
    {
        throw ServiceException(e.what());
    }
}

void ServiceProdus::delete_produs(int id)
{
    try
    {
        repo.delete_produs(id);
        notify();
    }
    catch(exception& e)
    {
        throw ServiceException(e.what());
    }
}

void ServiceProdus::modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou)
{
    try
    {
        Produs produs{id, nume_nou, tip_nou, pret_nou};
        val.validate(produs);
        repo.modify_produs(id, nume_nou, tip_nou, pret_nou);
        notify();
    }
    catch(exception& e)
    {
        throw ServiceException(e.what());
    }
}

[[nodiscard]] Produs& ServiceProdus::find_produs(int id)
{
    try
    {
        return repo.find_produs(id);
    }
    catch(exception& e)
    {
        throw ServiceException(e.what());
    }
}

[[nodiscard]] const vector<Produs>& ServiceProdus::get_all_produse() const
{
    return repo.get_all_produse();
}

int ServiceProdus::count_vowels(const string& word)
{
    int cnt = 0;
    for (auto& l : word)
    {
        if (strchr("aeiouAEIOU", l) != nullptr)
        {
            cnt++;
        }
    }
    return cnt;
}

map<string, int> ServiceProdus::get_count_type(const vector<Produs>& produse)
{
    map<string, int> get_count_type;
    for (auto& produs : produse)
    {
        get_count_type[produs.get_tip()]++;
    }
    return get_count_type;
}

vector<Produs> ServiceProdus::sort_by_price(const vector<Produs>& produse)
{
    vector<Produs> sorted_produse = produse;
    std::ranges::sort(sorted_produse, [](const Produs& a, const Produs& b)
    {
        return a.get_pret() < b.get_pret();
    });
    return sorted_produse;
}