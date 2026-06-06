//
// Created by Alexandra on 5/17/2026.
//

#ifndef DOCTORI_SERVICE_DOCTOR_H
#define DOCTORI_SERVICE_DOCTOR_H

#include <utility>
#include "../repo/repo_doctor.h"
using std::copy_if;
class ServiceException : public std::exception
{
private:
    string message;
public:
    explicit ServiceException(string _message) : message(std::move(_message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceDoctor
{
private:
    Repo& repo;
public:
    virtual ~ServiceDoctor() = default;
    ServiceDoctor(Repo& _repo) : repo{_repo} {}
    ServiceDoctor() = delete;
    ServiceDoctor(const ServiceDoctor &) = delete;

    /**
     * Adauga un doctor in repo
     * @param cnp Cnp-ul doctorului de adaugat
     * @param nume Numele doctorului de adaugat
     * @param prenume Prenumele doctorului de adaugat
     * @param sectie Sectia doctorului de adaugat
     * @param concediu 1/0 daca doctorul este/nu este in concediu
     */
    void add_doctor(const string& cnp, const string& nume, const string& prenume, const string& sectie, int concediu)
    {
        try
        {
            Doctor doctor{cnp, nume, prenume, sectie, concediu};
            repo.add_doctor(doctor);
        }
        catch (std::exception &e)
        {
            throw ServiceException(e.what());
        }
    }

    /**
     * Cauta un doctor in repo cu cnp-ul dat
     * @param cnp Cnp-ul doctorului de cautat
     * @return Doctorul gasit cu cnp-ul dat
     */
    virtual Doctor& find_doctor(const string &cnp)
    {
        try
        {
            return repo.find_doctor(cnp);
        }
        catch (std::exception &e)
        {
            throw ServiceException(e.what());
        }
    }

    /**
     * @return Toti doctorii din repo
     */
    [[nodiscard]] virtual const vector<Doctor> &get_all_doctori() const
    {
        return repo.get_all_doctori();
    }

    /**
     * Filtreaza vectorul de doctori in functie de nume
     * @param doctori Vectorul de doctori care trebuie filtrat
     * @param nume Numele dupa care se realizeaza filtrarea
     * @return Vectorul filtrat in functie de nume
     */
    static vector<Doctor> filter_by_nume(const vector<Doctor>& doctori, const string &nume)
    {
        vector<Doctor> filtered_array;
        copy_if(doctori.begin(), doctori.end(), back_inserter(filtered_array),
            [nume](const Doctor& doctor)
            {
                return nume == doctor.get_nume();
            });
        return filtered_array;
    }

    /**
     * Filtreaza vectorul de doctori in functie de sectie
     * @param doctori Vectorul de doctori care trebuie filtrar
     * @param sectie Sectia dupa care se realizeaza filtrarea
     * @return Vectorul filtrat
     */
    static vector<Doctor> filter_by_sectie(const vector<Doctor>& doctori, const string &sectie)
    {
        vector<Doctor> filtered_array;
        copy_if(doctori.begin(), doctori.end(), back_inserter(filtered_array),
            [sectie](const Doctor& doctor)
            {
                return sectie == doctor.get_sectie();
            });
        return filtered_array;
    }

    /**
     * Cauta doctorul din repo cu numele si prenumele data
     * @param nume Numele doctorului
     * @param prenume Prenumele doctorului
     * @return Doctorul care are acest nume si acest prenume
     */
    Doctor& find_by_nume_prenume (const string &nume, const string &prenume) const
    {
        try
        {
            return repo.find_by_nume_prenume(nume, prenume);
        }
        catch (std::exception &e)
        {
            throw ServiceException(e.what());
        }

    }
};

#endif //DOCTORI_SERVICE_DOCTOR_H
