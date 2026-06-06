//
// Created by Alexandra on 5/17/2026.
//

#ifndef DOCTORI_REPO_DOCTOR_H
#define DOCTORI_REPO_DOCTOR_H

#include "../domain/doctor.h"
#include <exception>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::vector;
using std::find_if;
using std::stringstream;
//adaugare
//cautare
class RepoException : public std::exception
{
private:
    string message;
public:
    explicit RepoException(string _message) : message(std::move(_message)) {}
    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};

class Repo {
public:
    Repo() = default;
    virtual ~Repo() = default;

    virtual void add_doctor(const Doctor &doctor) = 0;
    virtual Doctor& find_doctor(const string &cnp) = 0;
    [[nodiscard]] virtual const vector<Doctor> &get_all_doctori() const = 0;
    virtual Doctor& find_by_nume_prenume (const string &nume, const string &prenume) = 0;
};

class RepoDoctor : public Repo
{
protected:
    vector<Doctor> doctori;

public:
    /**
     * Adauga un doctor in memorie
     * @param doctor Doctorul de adaugat
     */
    void add_doctor(const Doctor &doctor) override
    {
        auto it = find_if(doctori.begin(), doctori.end(),
            [doctor](const Doctor &d)
            {
                return doctor.get_cnp() == d.get_cnp();
            });
        if (it != doctori.end())
        {
            throw RepoException("Doctor already exists");
        }
        doctori.emplace_back(doctor);
    }

    /**
     * Cauta un doctor in functie de cnp
     * @param cnp Cnp-ul doctorului de cautat
     * @return Doctorul gssit
     */
    Doctor& find_doctor(const string &cnp) override
    {
        auto it = find_if(doctori.begin(), doctori.end(),
            [cnp](const Doctor &d)
            {
                return cnp == d.get_cnp();
            });
        if (it == doctori.end())
        {
            throw RepoException("Doctor does not exist");
        }
        return *it;
    }

    /**
     * @return Toti doctorii stocati in aplicatie
     */
    [[nodiscard]] const vector<Doctor> &get_all_doctori() const override
    {
        return doctori;
    }

    /**
     * Cauta un doctor in functie de nume si prenume
     * @param nume Numele doctorului de cautat
     * @param prenume Prenumele doctorului de cautat
     * @return Doctorul gasit cu acest nume si acest prenume
     */
    Doctor& find_by_nume_prenume (const string &nume, const string &prenume) override
    {
        auto it = find_if(doctori.begin(), doctori.end(),
            [nume, prenume](const Doctor &d)
            {
                return nume == d.get_nume() && prenume == d.get_prenume();
            });
        if (it == doctori.end())
        {
            throw RepoException("Doctor does not exist");
        }
        return *it;
    }
};

class RepoDoctorFile : public RepoDoctor
{
private:
    string filename;
    void load_from_file();
    void save_to_file();

public:
    RepoDoctorFile(string _filename) : filename(std::move(_filename))
    {
        load_from_file();
    }

    /**
     * Adauga un doctor in fisier
     * @param doctor Doctorul de adaugat
     */
    void add_doctor(const Doctor &doctor) override
    {
        RepoDoctor::add_doctor(doctor);
        save_to_file();
    }

    /**
     * Cauta un doctor in functie de cnp
     * @param cnp Cnp-ul doctorului de cautat
     * @return Doctorul gssit
     */
    Doctor& find_doctor(const string &cnp) override
    {
        return RepoDoctor::find_doctor(cnp);
    }

    /**
     * @return Toti doctorii stocati in aplicatie
     */
    [[nodiscard]] const vector<Doctor> &get_all_doctori() const override
    {
        return RepoDoctor::get_all_doctori();
    }

    /**
     * Cauta un doctor in functie de nume si prenume
     * @param nume Numele doctorului de cautat
     * @param prenume Prenumele doctorului de cautat
     * @return Doctorul gasit cu acest nume si acest prenume
     */
    Doctor& find_by_nume_prenume (const string &nume, const string &prenume) override
    {
        return RepoDoctor::find_by_nume_prenume(nume, prenume);
    }
};

#endif //DOCTORI_REPO_DOCTOR_H
