//
// Created by Alexandra on 5/10/2026.
//

#include "produs.h"

int Produs::get_id() const
{
    return id;
}

string Produs::get_nume() const
{
    return nume;
}

string Produs::get_tip() const
{
    return tip;
}

double Produs::get_pret() const
{
    return pret;
}

void Produs::set_nume(const string& nume_nou)
{
    nume = nume_nou;
}

void Produs::set_tip(const string& tip_nou)
{
    tip = tip_nou;
}

void Produs::set_pret(double pret_nou)
{
    pret = pret_nou;
}