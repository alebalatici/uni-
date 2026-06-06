//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR_SERVICE_JUCATORI_H
#define JUCATOR_SERVICE_JUCATORI_H
#include <string>
#include <utility>
#include "../repo/repo_jucatori.h"
using std::sort;
class ServiceException : public std::exception
{
    private:
    string message;
    public:
    explicit ServiceException(string message) : message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceJucatori {
private:
    Repo& repo;
public:
    ServiceJucatori(Repo& _repo): repo{_repo} {}
    virtual ~ServiceJucatori() = default;
    ServiceJucatori(const ServiceJucatori&) = delete;
    ServiceJucatori() = delete;

    void add_jucator(const string& nume, const string& tara, int numar_puncte, int ranking)
    {
        try
        {
            Jucator jucator{nume, tara, numar_puncte, ranking};
            repo.add_jucator(jucator);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    void delete_jucator(const string& nume)
    {
        try
        {
            repo.delete_jucator(nume);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    Jucator& find_jucator(const string& nume) const
    {
        try
        {
            return repo.find_jucator(nume);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const
    {
        return repo.get_all_jucatori();
    }

    void modify_jucator(const string& _nume, const string& _tara, int _numar_puncte, int _ranking)
    {
        try
        {
            repo.modify_jucator(_nume, _tara, _numar_puncte, _ranking);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }

    vector<Jucator> recalculeaza_rank(const vector<Jucator>& jucatori)
    {
        vector<Jucator> jucatori_sortati = jucatori;
        sort(jucatori_sortati.begin(), jucatori_sortati.end(),
            [](const Jucator& a, const Jucator& b)
            {
                return a.get_numar_puncte() > b.get_numar_puncte();
            });

        int rank = 1;
        for (auto &j : jucatori_sortati)
        {
            modify_jucator(j.get_nume(), j.get_tara(), j.get_numar_puncte(), rank++);
        }

        return jucatori_sortati;
    }

    void delete_m_jucatori_punctaj(int m)
    {
        if (m > (int)repo.get_all_jucatori().size() / 2)
        {
            throw ServiceException{"Too many players to delete"};
        }
        vector<Jucator> jucatori_sortati = repo.get_all_jucatori();
        //sortare crescatoare dupa puncte
        sort(jucatori_sortati.begin(), jucatori_sortati.end(),
            [](const Jucator& a, const Jucator& b)
                {
                    return a.get_numar_puncte() < b.get_numar_puncte();
                });

        //se sterg primii m jucatori cu punctajele cele mai mici
        for (int i = 0; i < m; i++)
        {
            delete_jucator(jucatori_sortati[i].get_nume());
        }
    }

    void delete_m_jucatori_ranking(int m)
    {
        if (m > (int)repo.get_all_jucatori().size() / 2)
        {
            throw ServiceException{"Too many players to delete"};
        }
        vector<Jucator> jucatori_sortati = repo.get_all_jucatori();
        sort(jucatori_sortati.begin(), jucatori_sortati.end(),
            [](const Jucator& a, const Jucator& b)
                {
                    return a.get_ranking() > b.get_ranking();
                });
        for (int i = 0; i < m; i++)
        {
            delete_jucator(jucatori_sortati[i].get_nume());
        }
    }
};



#endif //JUCATOR_SERVICE_JUCATORI_H
