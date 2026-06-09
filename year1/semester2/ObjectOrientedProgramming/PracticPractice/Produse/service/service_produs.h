//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_SERVICE_PRODUS_H
#define PRODUSE_SERVICE_PRODUS_H

#include <utility>
#include <cstring>
#include <map>

#include "../domain/validator.h"
#include "../repo/repo_produs.h"
#include "../observer/observer.h"

using std::map;
class ServiceException : public exception
{
private:
    string msg;
public:
    explicit ServiceException(string msg) : msg(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
};

class ServiceProdus : public Observable {
    Repo& repo;
    Validator& val;
    public:
    ServiceProdus(Repo& _repo, Validator& _val) : repo{_repo}, val{_val} {}
    ServiceProdus(const ServiceProdus& ot) = delete;
    ServiceProdus() = delete;
    virtual ~ServiceProdus() = default;

    void add_produs(int id, const string& nume, const string& tip, double pret);
    void delete_produs(int id);
    void modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou);
    [[nodiscard]] Produs& find_produs(int id);
    [[nodiscard]] const vector<Produs>& get_all_produse() const;
    static int count_vowels(const string& word);
    static map<string, int> get_count_type(const vector<Produs>& produse);
    static vector<Produs> sort_by_price(const vector<Produs>& produse);
};

#endif //PRODUSE_SERVICE_PRODUS_H