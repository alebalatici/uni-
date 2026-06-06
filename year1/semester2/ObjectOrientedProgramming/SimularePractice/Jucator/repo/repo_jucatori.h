//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR_REPO_JUCATORI_H
#define JUCATOR_REPO_JUCATORI_H

#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include "../domain/jucator.h"
#include "../utils/file_utils.h"
using std::vector;
using std::find_if;
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

    virtual void add_jucator(const Jucator& jucator) = 0;
    virtual void delete_jucator(const string& nume) = 0;
    virtual Jucator& find_jucator(const string& nume) = 0;
    virtual void modify_jucator(const string& _nume, const string& _tara, int _numar_puncte, int _ranking) = 0;
    [[nodiscard]] virtual const vector<Jucator>& get_all_jucatori() const = 0;
};

class RepoJucatori : public Repo {
public:
protected:
    vector<Jucator> jucatori;
public:
    void add_jucator(const Jucator& jucator) override
    {
        auto it = find_if(jucatori.begin(), jucatori.end(),
            [jucator](const Jucator& j)
            {
                return j.get_nume() == jucator.get_nume();
            });
        if (it != jucatori.end())
        {
            throw RepoException("Jucator already exists");
        }
        jucatori.push_back(jucator);
    }

    void delete_jucator(const string& nume) override
    {
        Jucator& j = find_jucator(nume);
        for (auto it = jucatori.begin(); it != jucatori.end(); ++it)
        {
            if (*it == j)
            {
                jucatori.erase(it);
                return;
            }
        }
    }

    Jucator& find_jucator(const string& nume) override
    {
        auto it = find_if(jucatori.begin(), jucatori.end(),
            [nume](const Jucator& j)
            {
                return j.get_nume() == nume;
            });
        if (it == jucatori.end())
        {
            throw RepoException("Jucator does not exist");
        }
        return *it;
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const override
    {
        return jucatori;
    }

    void modify_jucator(const string& _nume, const string& _tara, int _numar_puncte, int _ranking) override
    {
        Jucator& j = find_jucator(_nume);
        j.set_tara(_tara);
        j.set_numar_puncte(_numar_puncte);
        j.set_ranking(_ranking);
    }
};

class RepoJucatoriFile : public RepoJucatori
{
private:
    string filename;
    void load_from_file();
public:
    RepoJucatoriFile(string  _filename) : filename{std::move(_filename)}
    {
        load_from_file();
    }
    void add_jucator(const Jucator& jucator) override
    {
        RepoJucatori::add_jucator(jucator);
    }
    void delete_jucator(const string& nume) override
    {
        RepoJucatori::delete_jucator(nume);
    }
    Jucator& find_jucator(const string& nume) override
    {
        return RepoJucatori::find_jucator(nume);
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const override
    {
        return RepoJucatori::get_all_jucatori();
    }

    void modify_jucator(const string& _nume, const string& _tara, int _numar_puncte, int _ranking) override
    {
        RepoJucatori::modify_jucator(_nume, _tara, _numar_puncte, _ranking);
    }
};

#endif //JUCATOR_REPO_JUCATORI_H
