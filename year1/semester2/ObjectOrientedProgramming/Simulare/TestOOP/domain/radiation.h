//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_RADIATION_H
#define TESTOOP_RADIATION_H

#include <string>
#include <utility>
#include <ostream>
using std::string;
class Radiation {
    private:
    int id;
    string description;
    double frecventa;
    string tip_frecventa;

    public:
    Radiation(int _id, string _description, double _frecventa, string tip_frecventa) : id{_id}, description{std::move(_description)}, frecventa{_frecventa}, tip_frecventa {std::move(tip_frecventa)} {};

    /**
     * Returneaza id-ul
     * @return id-ul
     */
    [[nodiscard]] int get_id () const { return id; }

    /**
     * Returneaza descrierea
     * @return descrierea
     */
    [[nodiscard]] string get_description() const { return description; }

    /**
     * Returneaza frecventa
     * @return Frecventa
     */
    [[nodiscard]] double get_frecventa() const { return frecventa; }

    /**
     * Returneaza tipul frecventei
     * @return Tipul frecventei
     */
    [[nodiscard]] string get_tip_frecventa() const { return tip_frecventa; }

    Radiation(const Radiation &radiation) = default;

    /**
     * Operatorul egal
     * @param ot O alta radiatie cu care se compara
     * @return True/False
     */
    bool operator==(const Radiation& ot) const
    {
        return id == ot.id && description == ot.description && frecventa == ot.frecventa && tip_frecventa == ot.tip_frecventa ;
    }

    friend std::ostream& operator<<(std::ostream& os, const Radiation& radiation)
    {
        os << radiation.id << radiation.description << radiation.frecventa << radiation.tip_frecventa;
        return os;
    }
};



#endif //TESTOOP_RADIATION_H
