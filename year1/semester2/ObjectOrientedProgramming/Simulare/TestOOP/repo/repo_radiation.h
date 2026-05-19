//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_REPO_RADIATION_H
#define TESTOOP_REPO_RADIATION_H

#include <exception>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "../domain/radiation.h"
using std::vector;
using std::find_if;
using std::stringstream;
using std::ifstream;
using std::ofstream;
class RepoException: public std::exception
{
    private:
    string message;
    public:
    explicit RepoException(string message) : message(std::move(message)) {}
    [[nodiscard]] const char * what() const noexcept override { return message.c_str(); }
};

class Repo {
    public:
    virtual ~Repo() = default;
    Repo() = default;
    virtual void add_radiation(const Radiation &radiation) = 0;
    [[nodiscard]] virtual const vector<Radiation>& get_all_radiatii() const = 0;
};

class RepoRadiation : public Repo
{
    protected:
    vector<Radiation> radiatii;
    public:
    /**
     * Adauga o radiatie in lista de radiatii
     * @param radiation Raidatia de adaugat
     */
    void add_radiation(const Radiation &radiation) override
    {
        auto it = find_if(radiatii.begin(), radiatii.end(),
            [radiation](const Radiation& r)
            {
                return r.get_id() == radiation.get_id();
            });
        if (it != radiatii.end())
        {
            throw RepoException("Radiation already exists\n");
        }
        radiatii.push_back(radiation);
    }

    /**
     * Returneaza vectorul cu toate radiatiile
     * @return Vectorul cu toate radiatiile
     */
    [[nodiscard]] const vector<Radiation>& get_all_radiatii() const override
    {
        return radiatii;
    }
};

class RepoRadiationFile : public RepoRadiation
{
private:
    string filename;

    /**
     * Incarca datele din fisier in memorie
     */
    void load_from_file()
    {
        ifstream fin(filename);
        if (!fin.is_open())
        {
            throw RepoException("Could not open file\n");
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

            int id;
            string description;
            double frecventa;
            string tip_frecventa;

            string current_item;
            int item_no = 0;
            stringstream linestream(line);
            try
            {
                 while (getline(linestream, current_item, ','))
                {
                    switch (item_no)
                    {
                        case 0: id = stoi(current_item); break;
                        case 1: description = current_item; break;
                        case 2: frecventa = stod(current_item); break;
                        case 3: tip_frecventa = current_item; break;
                        default: break;
                    }
                    item_no++;
                }
                if (item_no != 4)
                {
                    throw RepoException("Invalid item number\n");
                }
                Radiation radiation{id, description, frecventa, tip_frecventa};
                RepoRadiation::add_radiation(radiation);
            }
            catch (std::exception& e)
            {
                throw RepoException(e.what());
            }
        }
    }

public:
    RepoRadiationFile(string _filename) : filename(std::move(_filename))
    {
        load_from_file();
    }

    /**
     * Adauga o radiatie
     * @param radiation Radiatia de adaugat
     */
    void add_radiation(const Radiation &radiation) override
    {
        RepoRadiation::add_radiation(radiation);
    }

    /**
     * Retunreaza vectorul cu toate radiatiile
     * @return Vectorul cu toate radiatiile
     */
    [[nodiscard]]  const vector<Radiation>& get_all_radiatii() const override
    {
        return RepoRadiation::get_all_radiatii();
    }
};

#endif //TESTOOP_REPO_RADIATION_H
