//
// Created by Alexandra on 5/16/2026.
//

#ifndef GAMINGSTORE_JOC_H
#define GAMINGSTORE_JOC_H

#include <string>
#include <utility>
#include <ostream>
using std::string;
using std::ostream;
class Joc {
private:
    string titlu;
    double pret;
    string platforma;
    int age_rating;
public:
    Joc(string _titlu, double _pret, string platforma, int _age_rating) : titlu{std::move(_titlu)}, pret{_pret}, platforma{std::move(platforma)}, age_rating{_age_rating} {}
    Joc(const Joc& ot) = default;
    bool operator==(const Joc& ot) const
    {
        return titlu == ot.titlu && pret == ot.pret && platforma == ot.platforma && age_rating == ot.age_rating;
    }

    friend ostream& operator<<(ostream& os, const Joc& joc)
    {
        os << "Titlu: " << joc.titlu << " | Pret: " << joc.pret << " | Platforma: " << joc.platforma << " | Age-Rating: " << joc.age_rating;
        return os;
    }

    [[nodiscard]] string get_titlu() const
    {
        return titlu;
    }

    [[nodiscard]] double get_pret() const
    {
        return pret;
    }

    [[nodiscard]] string get_platforma() const
    {
        return platforma;
    }

    [[nodiscard]] int get_age_rating() const
    {
        return age_rating;
    }
};



#endif //GAMINGSTORE_JOC_H
