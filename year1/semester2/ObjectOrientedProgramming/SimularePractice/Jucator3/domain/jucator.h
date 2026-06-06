//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR3_JUCATOR_H
#define JUCATOR3_JUCATOR_H

#include <string>
#include <ostream>
#include <utility>
using std::string;
class Jucator {
private:
    string nume;
    string tara;
    int numar_puncte;
    int ranking;
public:
    Jucator(string _nume, string _tara, int _numar_puncte, int _ranking) : nume{std::move(_nume)}, tara{std::move(_tara)}, numar_puncte{_numar_puncte}, ranking{_ranking} {}
    [[nodiscard]] string get_nume() const {return nume;}
    [[nodiscard]] string get_tara() const {return tara;}
    [[nodiscard]] int get_numar_puncte() const {return numar_puncte;}
    [[nodiscard]] int get_ranking() const {return ranking;}

    Jucator(const Jucator &ot) = default;
    bool operator==(const Jucator &ot) const
    {
        return nume == ot.nume && tara == ot.tara && numar_puncte == ot.numar_puncte && ranking == ot.ranking;
    }

    friend std::ostream &operator<<(std::ostream &os, const Jucator &jucator)
    {
        os << "Nume: " << jucator.nume << " | Tara: " << jucator.tara << " | Numar puncte: " << jucator.numar_puncte << " | Ranking: " << jucator.ranking;
        return os;
    }
};



#endif //JUCATOR3_JUCATOR_H
