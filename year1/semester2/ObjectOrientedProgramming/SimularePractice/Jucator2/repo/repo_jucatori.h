//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR2_REPO_JUCATORI_H
#define JUCATOR2_REPO_JUCATORI_H
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <utility>
#include <vector>
#include "../domain/jucator.h"
#include <fstream>
#include <iostream>
#include <qtextstream.h>
#include <sstream>
using std::vector;
using std::find_if;
using std::ifstream;
using std::ostream;
using std::stringstream;
class RepoException : public std::exception
{
    private:
    string message;
    public:
    explicit RepoException(string message) : message{std::move(message)} {};
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Repo {
    public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_jucator(const Jucator& jucator) = 0;
    [[nodiscard]] virtual const vector<Jucator>& get_all_jucatori() const = 0;
    virtual Jucator& find_jucator(const string& nume, const string& tara) = 0;
};

class RepoJucatori : public Repo
{
    protected:
    vector<Jucator> jucatori;
    public:
    void recalculare_rank_uri()
    {
        std::sort(jucatori.begin(), jucatori.end(),
            [](Jucator& a, Jucator& b)
            {
                return a.get_numar_puncte() > b.get_numar_puncte();
            });
        int index = 0;
        for (auto &j : jucatori)
        {
            j.set_rank(++index);
        }
    }

    /**
     * Adauga un jucator in repo
     * @param jucator Jucatorul de adaugat
     */
    void add_jucator(const Jucator& jucator) override
    {
        auto it = std::find_if((jucatori.begin()), jucatori.end(),
            [&jucator](const Jucator& j)
            {
                return jucator.get_nume() == j.get_nume() && jucator.get_tara() == j.get_tara();
            });
        if (it != jucatori.end())
        {
            throw RepoException("Jucator already exists");
        }
        jucatori.emplace_back(jucator);
       // recalculare_rank_uri();
    }

    /**
     * Returneaza vectorul cu toti jucatorii din repo
     * @return Vectorul cu toti jucatorii din repo
     */
    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const override
    {
        return jucatori;
    }

    /**
     * Cauta un jucator un functie de nume si tara
     * @param nume Numele jucatorului
     * @param tara Tara jucatorului
     * @return Jucatorul gasit
     */
    Jucator& find_jucator(const string& nume, const string& tara) override
    {
        auto it = std::find_if(jucatori.begin(), jucatori.end(),
            [nume, tara](const Jucator& j)
            {
                return j.get_nume() == nume && j.get_tara() == tara;
            });
        if (it == jucatori.end())
        {
            throw RepoException("Jucator not found");
        }
        return *it;
    }


};

class RepoJucatoriFile : public RepoJucatori
{
private:
    string filename;

    /**
     * Incarca in memorie toti jucatorii din fisierul dat
     */
    void load_from_file()
    {
        ifstream fin{filename};
        if (!fin.is_open())
        {
            throw RepoException("Could not open file");
        }
        string line;
        while (getline(fin, line))
        {
            while (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            if (line.empty())
            {
                continue;
            }

            string nume;
            string tara;
            int numar_puncte;
            int ranking;

            string current_item;
            int item_no = 0;
            stringstream linestream(line);
            try
            {
                while (getline(linestream, current_item, ','))
                {
                    switch (item_no)
                    {
                    case 0: nume = current_item; break;
                    case 1: tara = current_item; break;
                    case 2: numar_puncte = stoi(current_item); break;
                    case 3: ranking = stoi(current_item); break;
                    default: break;
                    }
                    item_no++;
                }
                if (item_no != 4)
                {
                throw RepoException("Formatting error on line " + line + " in file " + filename);
                }
                Jucator jucator{nume, tara, numar_puncte, ranking};
                RepoJucatori::add_jucator(jucator);
            }
            catch (std::exception& e)
            {
                throw RepoException(e.what());
            }
        }
    }

public:
    RepoJucatoriFile(string _filename) : filename{std::move(_filename)}
    {
        load_from_file();
        recalculare_rank_uri();
    }
    /**
     * Adauga in memorie un jucator
     * @param jucator Jucatorul de adaugat
     */
    void add_jucator(const Jucator& jucator) override
    {
        RepoJucatori::add_jucator(jucator);
        recalculare_rank_uri();
    }

    /**
     * Returneaza lista de jucatori
     * @return Lista de jucatori
     */
    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const override
    {
        return RepoJucatori::get_all_jucatori();
    }

    Jucator& find_jucator(const string& nume, const string& tara) override
    {
        return RepoJucatori::find_jucator(nume, tara);
    }
};

#endif //JUCATOR2_REPO_JUCATORI_H
