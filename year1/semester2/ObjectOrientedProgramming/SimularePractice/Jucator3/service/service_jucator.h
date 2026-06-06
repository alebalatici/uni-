//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR3_SERVICE_JUCATOR_H
#define JUCATOR3_SERVICE_JUCATOR_H

#include <utility>
#include "../repo/repo_jucator.h"

class ServiceException : public std::exception
{
    private:
    string message;
    public:
    explicit ServiceException(string message) : message(std::move(message)) {};
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class ServiceJucator {
    private:
    Repo& repo;
    public:
    ServiceJucator(Repo& _repo) : repo{_repo} {};
    virtual ~ServiceJucator() = default;
    ServiceJucator(const ServiceJucator&) = delete;
    ServiceJucator() = delete;

    void add_jucator(const string& nume, const string& tara, int numar_puncte, int ranking)
    {
        try
        {
            Jucator jucator{nume, tara, numar_puncte, ranking};
            repo.add_jucator(jucator);
        }
        catch(std::exception& e)
        {
            throw ServiceException(e.what());
        }
    }

    [[nodiscard]] const vector<Jucator>& get_all_jucatori()
    {
        return repo.get_all_jucatori();
    }
};



#endif //JUCATOR3_SERVICE_JUCATOR_H
