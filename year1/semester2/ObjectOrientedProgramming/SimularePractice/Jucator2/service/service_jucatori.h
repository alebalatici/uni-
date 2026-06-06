//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR2_SERVICE_JUCATORI_H
#define JUCATOR2_SERVICE_JUCATORI_H

#include <utility>
#include <algorithm>
#include "../repo/repo_jucatori.h"
using std::sort;
using std::copy_if;
class ServiceException : public std::exception
{
    private:
    string message;
    public:
    explicit ServiceException(string message): message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceJucatori {
    private:
    Repo& repo;
    public:
    virtual ~ServiceJucatori() = default;
    ServiceJucatori(Repo& _repo): repo{_repo} {}
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

    [[nodiscard]] const vector<Jucator>& get_all_jucatori() const
    {
        return repo.get_all_jucatori();
    }

    static vector<string> get_all_countries(const vector<Jucator>& jucatori)
    {
        vector<string> countries;
        vector<Jucator> sorted_by_country = jucatori;
        sort(sorted_by_country.begin(), sorted_by_country.end(),
            [](const Jucator& a, const Jucator& b)
            {
                return a.get_tara() < b.get_tara();
            });
        int i = 0;
        while (i < size(sorted_by_country))
        {
            string country = sorted_by_country[i].get_tara();
            while (i < size(sorted_by_country) && sorted_by_country[i].get_tara() == country )
            {
                i++;
            }
            countries.push_back(country);
        }
        return countries;
    }

    static vector<Jucator> filter_by_country(const vector<Jucator>& jucatori, const string& country)
    {
        vector<Jucator> filtered_jucatori;
        copy_if(jucatori.begin(), jucatori.end(),
            back_inserter(filtered_jucatori),
            [country](const Jucator& j)
            {
                return j.get_tara() == country;
            });
        return filtered_jucatori;
    }

     Jucator& find_jucator(const string& nume, const string& tara)
    {
        try
        {
            return repo.find_jucator(nume, tara);
        }
        catch (std::exception& e)
        {
            throw ServiceException{e.what()};
        }
    }
};

#endif //JUCATOR2_SERVICE_JUCATORI_H
