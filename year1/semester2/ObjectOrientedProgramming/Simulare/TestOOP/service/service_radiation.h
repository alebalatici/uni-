//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_SERVICE_RADIATION_H
#define TESTOOP_SERVICE_RADIATION_H

#include <utility>
#include <cstring>
#include "../repo/repo_radiation.h"
#include "../domain/validator.h"
using std::copy_if;
class ServiceException : public std::exception
{
    private:
    string message;
    public:
    explicit ServiceException(string message) : message(std::move(message)) {}
    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};

class ServiceRadiation {
private:
    Validator& val;
    Repo& repo;
public:
    ServiceRadiation(Repo& _repo, Validator& _val) : repo{_repo}, val {_val} {}

    /**
     * Adauga o radiatie
     * @param id Id-ul radiatiei
     * @param description Descrierea radiatiei
     * @param frecventa Frecventa radiatiei
     * @param tip_frecventa Tipul frecventei radiatiei
     */
    void add_radiation(int id, const string& description, double frecventa, const string& tip_frecventa)
    {
        try
        {
            Radiation radiation{id, description, frecventa, tip_frecventa};
            val.validate(radiation);
            repo.add_radiation(radiation);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    /**
     * Returneaza vectorul cu toate radiatiile
     * @return Vectorul cu toate radiatiile
     */
    [[nodiscard]] const vector<Radiation>& get_all_radiatii() const
    {
        return repo.get_all_radiatii();
    }

    /**
     * Filtreaza radiatiile in functe de frecventa
     * @param radiations Radiatiile de filtrat
     * @param frecventa Frecventa
     * @return Vectorul de radiatii filtrate
     */
    static vector<Radiation> filtrare_frecventa(const vector<Radiation>& radiations, double frecventa)
    {
        vector<Radiation> filtered;
        copy_if(radiations.begin(), radiations.end(),
            back_inserter(filtered),
            [frecventa](const Radiation& r) -> bool
            {
                return r.get_frecventa() <= frecventa;
            });
        return filtered;
    }

    /**
     * Filtreaza in functie de un string
     * @param radiations Vectorul de radiatii
     * @param str Stringul dupa care se realizeaza filtrarea
     * @return
     */
    static vector<Radiation> filtrare_string(const vector<Radiation>& radiations, const string& str)
    {
        vector<Radiation> filtered;
        copy_if(radiations.begin(), radiations.end(),
            back_inserter(filtered),
            [str](const Radiation& r) -> bool
            {
                return strstr(r.get_description().c_str(), str.c_str()) != nullptr || strstr(r.get_tip_frecventa().c_str(), str.c_str()) != nullptr;
            });
        return filtered;
    }
};

#endif //TESTOOP_SERVICE_RADIATION_H
