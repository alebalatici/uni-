//
// Created by Alexandra on 5/17/2026.
//

#ifndef DOCTORI_DOCTOR_H
#define DOCTORI_DOCTOR_H

#include <ostream>
#include <string>
#include <utility>
using std::string;
class Doctor {
private:
    string cnp;
    string nume;
    string prenume;
    string sectie;
    int concediu;
public:
    Doctor(string _cnp, string _nume, string _prenume, string _sectie, int _concediu) : cnp{std::move(_cnp)}, nume{std::move(_nume)}, prenume{std::move(_prenume)}, sectie{std::move(_sectie)}, concediu{_concediu} {};
    Doctor(const Doctor& ot) = default;

    bool operator==(const Doctor& ot) const
    {
        return cnp == ot.cnp && nume == ot.nume && prenume == ot.prenume && sectie == ot.sectie && concediu == ot.concediu;
    }

    friend std::ostream& operator<<(std::ostream& os, const Doctor& doctor)
    {
        os << "Cnp: " << doctor.cnp << " | Nume: " << doctor.nume << " | Prenume: " << doctor.prenume << " | Sectie: " << doctor.sectie << " | Concediu: " << doctor.concediu;
        return os;
    }

    [[nodiscard]] string get_cnp() const
    {
        return cnp;
    }

    [[nodiscard]] string get_nume() const
    {
        return nume;

    }

    [[nodiscard]] string get_prenume() const
    {
        return prenume;
    }

    [[nodiscard]] string get_sectie() const
    {
        return sectie;
    }

    [[nodiscard]] int get_concediu() const
    {
        return concediu;
    }
};



#endif //DOCTORI_DOCTOR_H
