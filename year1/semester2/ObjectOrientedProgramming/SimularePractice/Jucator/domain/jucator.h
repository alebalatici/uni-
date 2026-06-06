//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR_JUCATOR_H
#define JUCATOR_JUCATOR_H

#include <string>
#include <ostream>
#include <utility>
using std::string;
using std::ostream;
class Jucator {
private:
    string nume;
    string tara;
    int numar_puncte;
    int ranking;
public:
    Jucator(string _nume, string _tara, int _numar_puncte, int _ranking) : nume{std::move(_nume)}, tara{std::move(_tara)}, numar_puncte{_numar_puncte}, ranking{_ranking} {}
    [[nodiscard]] string get_nume() const {return nume;};
    [[nodiscard]] string get_tara() const {return tara;};
    [[nodiscard]] int get_numar_puncte() const {return numar_puncte;};
    [[nodiscard]] int get_ranking() const {return ranking;};
    Jucator(const Jucator& ot) = default;
    bool operator==(const Jucator& ot) const
    {
        return nume == ot.nume && tara == ot.tara && numar_puncte == ot.numar_puncte && ranking == ot.ranking;
    }

    friend ostream& operator<<(ostream& os, const Jucator& jucator)
    {
        os << "Nume: " << jucator.get_nume() << " | Tara: " << jucator.get_tara() << " | Numar puncte: " << jucator.get_numar_puncte() << " | Ranking: " << jucator.get_ranking();
        return os;
    }

    void set_tara(const string& _tara) {tara = _tara;}
    void set_numar_puncte(int _numar_puncte) {numar_puncte = _numar_puncte;}
    void set_ranking(int _ranking) {ranking = _ranking;}
};

#endif //JUCATOR_JUCATOR_H
