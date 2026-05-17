//
// Created by Alexandra on 5/16/2026.
//

#ifndef GAMINGSTORE_REPO_JOC_H
#define GAMINGSTORE_REPO_JOC_H

#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include "../domain/joc.h"
#include <algorithm>
//vizualizarea => get_all_jocuri()
//fisier => adaugare
//selectare => find
using std::vector;
using std::find_if;
using std::ifstream;
using std::ofstream;
using std::stringstream;
class RepoException : public std::exception
{
    private:
    string message;
    public:
    explicit RepoException(string  message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class Repo {
    public:
    Repo() = default;
    virtual ~Repo() = default;

    virtual void add_joc(const Joc& joc) = 0;
    virtual Joc& find_joc(const string& nume) = 0;
    [[nodiscard]] virtual const vector<Joc>& get_all_jocuri() const = 0;
};

class RepoJoc : public Repo
{
protected:
    vector<Joc> jocuri;
public:
    void add_joc(const Joc& joc) override
    {
        auto it = find_if(jocuri.begin(), jocuri.end(),
            [joc](const Joc& j)
            {
                return joc.get_titlu() == j.get_titlu();
            });

        if (it != jocuri.end())
        {
            throw RepoException("Joc already exists");
        }
        jocuri.push_back(joc);
    }

    Joc& find_joc(const string& nume) override
    {
        auto it = find_if(jocuri.begin(), jocuri.end(),
            [nume](const Joc& j)
            {
                return j.get_titlu() == nume;
            });
        if (it == jocuri.end())
        {
            throw RepoException("Joc not found");
        }
        return *it;
    }

    [[nodiscard]] const vector<Joc>& get_all_jocuri() const override
    {
        return jocuri;
    }
};

class RepoJocFile : public RepoJoc
{
private:
    string filename;
    void load_from_file();
    void save_to_file();
public:
    RepoJocFile(string _filename) : filename(std::move(_filename))
    {
        load_from_file();
    }

    void add_joc(const Joc& joc) override
    {
        RepoJoc::add_joc(joc);
        save_to_file();
    }


    Joc& find_joc(const string& nume) override
    {
        return RepoJoc::find_joc(nume);
    }

    [[nodiscard]] const vector<Joc>& get_all_jocuri() const override
    {
        return RepoJoc::get_all_jocuri();
    }
};

#endif //GAMINGSTORE_REPO_JOC_H
