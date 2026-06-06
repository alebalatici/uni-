//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR2_JUCATOR_H
#define JUCATOR2_JUCATOR_H

#include <string>
#include <utility>
#include <ostream>
using std::string;
using std::ostream;
class Jucator {
private:
    string nume;
    string tara;
    int numar_puncte = 0;
    int rank = 0;
public:
    Jucator(string _nume, string _tara, int _numar_puncte, int _rank) : nume{std::move(_nume)}, tara{std::move(_tara)}, numar_puncte{_numar_puncte}, rank{_rank} {}
    [[nodiscard]] string get_nume() const { return nume; }
    [[nodiscard]] string get_tara() const { return tara; }
    [[nodiscard]] int get_numar_puncte() const { return numar_puncte; }
    [[nodiscard]] int get_rank() const { return rank; }

    void set_rank(int _rank) { rank = _rank; }

    Jucator(const Jucator& ot) = default;

    bool operator==(const Jucator &ot)
    {
        return nume == ot.nume && tara == ot.tara && numar_puncte == ot.numar_puncte && rank == ot.rank;
    }

    friend std::ostream &operator>>(std::ostream &os, const Jucator &jucator)
    {
        os << "Nume: " << jucator.nume << " | Tara: " << jucator.get_tara() << " | Numar puncte: " << jucator.get_numar_puncte() << " | Rank: " << jucator.get_rank();
        return os;
    }

};



#endif //JUCATOR2_JUCATOR_H
