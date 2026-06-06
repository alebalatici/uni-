//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR3_REPO_JUCATOR_H
#define JUCATOR3_REPO_JUCATOR_H

#include <exception>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../domain/jucator.h"
using std::vector;
using std::find_if;
using std::ifstream;
using std::ofstream;
using std::stringstream;
class RepoException: public std::exception
{
    private:
    string message;
    public:
    explicit RepoException(string message): message(std::move(message)) {}
    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};

class Repo {
    public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_jucator(const Jucator& jucator) = 0;
    [[nodiscard]] virtual const vector<Jucator>& get_all_jucatori() const = 0;
};

class RepoJucator : public Repo
{
    protected:
    vector<Jucator> jucatori;
    public:
    void add_jucator(const Jucator& jucator) override
    {
        auto it = find_if(jucatori.begin(), jucatori.end(),
            [&jucator](const Jucator& j)
            {
                return jucator.get_nume() == j.get_nume() && jucator.get_tara() == j.get_tara();
            });
        if (it != jucatori.end())
        {
            throw RepoException("Jucator already exists");
        }
        jucatori.push_back(jucator);
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const override
    {
        return jucatori;
    }
};

class RepoJucatorFile : public RepoJucator
{
private:
    string filename;
    void load_from_file()
    {
        ifstream fin(filename);
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
                    throw RepoException("Formatting error on line " + line);
                }
                Jucator jucator{nume, tara, numar_puncte, ranking};
                RepoJucator::add_jucator(jucator);
            }
            catch (std::exception& e)
            {
                throw RepoException(e.what());
            }
        }
    }

public:
    RepoJucatorFile(string _filename) : filename{std::move(_filename)}
    {
        load_from_file();
    }

    void add_jucator(const Jucator& jucator) override
    {
        RepoJucator::add_jucator(jucator);
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const
    {
        return RepoJucator::get_all_jucatori();
    }
};

#endif //JUCATOR3_REPO_JUCATOR_H
