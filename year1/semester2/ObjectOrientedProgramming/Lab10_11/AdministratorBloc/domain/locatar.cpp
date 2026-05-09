#include "locatar.h"

#include <ostream>

int Locatar::get_apartment() const {
    return apartment;
}

string Locatar::get_nume() const {
    return nume;
}

double Locatar::get_suprafata() const {
    return suprafata;
}

string Locatar::get_tip() const {
    return tip;
}

bool Locatar::operator==(const Locatar &other) const {
    return apartment == other.apartment && nume == other.nume && suprafata == other.suprafata && tip == other.tip;
}

std::ostream& operator<<(std::ostream& os, const Locatar &locatar) {
    os << "Apartament: " << locatar.apartment << " | Nume: " << locatar.nume << " | Suprafata " << locatar.suprafata << " | Tip: " << locatar.tip;
    return os;
}

void Locatar::set_apartment(int apartament_nou) {
    this->apartment = apartament_nou;
}
void Locatar::set_nume(const string& nume_nou) {
    this->nume = nume_nou;
}
void Locatar::set_suprafata(double suprafata_noua) {
    this->suprafata = suprafata_noua;
}
void Locatar::set_tip(const string& tip_nou) {
    this->tip = tip_nou;
}