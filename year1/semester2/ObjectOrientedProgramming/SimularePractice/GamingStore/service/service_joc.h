//
// Created by Alexandra on 5/16/2026.
//

#ifndef GAMINGSTORE_SERVICE_JOC_H
#define GAMINGSTORE_SERVICE_JOC_H

#include <utility>
#include <algorithm>
#include "../repo/repo_joc.h"
using std::sort;
using std::copy_if;
class ServiceException : public std::exception
{
private:
    string message;
public:
    explicit ServiceException(string message) : message(std::move(message)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceJoc {
private:
    Repo& repo;
public:
    virtual ~ServiceJoc() = default;
    ServiceJoc(Repo& _repo) : repo{_repo} {};
    ServiceJoc(const ServiceJoc&) = delete;
    ServiceJoc() = delete;

    void add_joc(const string& nume, double pret, const string& platforma, int age_rating)
    {
        try
        {
            Joc joc{nume, pret, platforma, age_rating};
            repo.add_joc(joc);
        }
        catch (RepoException& e)
        {
            throw ServiceException(e.what());
        }
    }
    Joc& find_joc(const string& nume)
    {
        try
        {
            return repo.find_joc(nume);
        }
        catch (RepoException& e)
        {
            throw ServiceException(e.what());
        }
    }
    [[nodiscard]] virtual const vector<Joc>& get_all_jocuri() const
    {
        return repo.get_all_jocuri();
    }

    static vector<Joc> sort_by_price_ascending(const vector<Joc>& jocuri)
    {
        vector<Joc> sorted_array = jocuri;
        sort(sorted_array.begin(), sorted_array.end(),
            [](Joc& a, Joc& b){
                return a.get_pret() < b.get_pret();
            });
        return sorted_array;
    }

    static vector<Joc> filter_by_age_rating(const vector<Joc>& jocuri, int maximum_age_rating)
    {
        vector<Joc> filtered_array;
        copy_if(jocuri.begin(), jocuri.end(),
            std::back_inserter(filtered_array), [maximum_age_rating](const Joc& j)
            {
                return j.get_age_rating() < maximum_age_rating;
            });
        return filtered_array;
    }
};



#endif //GAMINGSTORE_SERVICE_JOC_H
