#ifndef ADMINISTRATORBLOC_LOCATAR_H
#define ADMINISTRATORBLOC_LOCATAR_H

#include <string>
using std::string;

class Locatar {
private:
    int apartment;
    string nume;
    double suprafata;
    string tip;
public:
    [[nodiscard]] int get_apartment() const;
    [[nodiscard]] string get_nume() const;
    [[nodiscard]] double get_suprafata() const;
    [[nodiscard]] string get_tip() const;
//const
    Locatar(int apartament, const string nume, double suprafata, const string tip) : apartment{apartament}, nume{nume}, suprafata{suprafata}, tip{tip} {}
//
    Locatar(const Locatar &ot): apartment{ot.apartment}, nume{ot.nume}, suprafata{ot.suprafata}, tip{ot.tip} {}

    void set_apartment(int apartament_nou);
    void set_nume(const string& nume_nou);
    void set_suprafata(double suprafata_noua);
    void set_tip(const string& tip_nou);

    bool operator==(const Locatar &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Locatar &locatar);
};



#endif //ADMINISTRATORBLOC_LOCATAR_H