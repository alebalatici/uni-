#ifndef ADMINISTRATORBLOC_SERVICE_LOCATARI_H
#define ADMINISTRATORBLOC_SERVICE_LOCATARI_H
#include <string>
#include <utility>
#include <algorithm>
#include "../domain/locatar.h"
#include "../repo/repo_locatari.h"
#include "../domain/validator.h"
using std::string;

class ServiceException : public std::exception {
    string msg;
public:
    ServiceException(string msg) : msg{std::move(msg)} {

    }

    string get_message() {
        return msg;
    }
};

class ServiceLocatari {
private:
    RepoLocatari& repo;
    ValidatorLocatar& val;
    MyVector<MyVector<Locatar>> undo_list;
public:
    ServiceLocatari(RepoLocatari& repo, ValidatorLocatar& val): repo{repo}, val{val} {}
    ServiceLocatari(const ServiceLocatari& ot) = delete;
    ServiceLocatari() = delete;

    void add_locatar(int apartament, const string& nume, double suprafata, const string& tip);

    Locatar& find_locatar(int numar_apartament);

    void delete_locatar(int numar_apartament);

    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou);

    const MyVector <Locatar>& get_all_locatari() const;

    static int count_vowels(const string& word);

    static MyVector <Locatar> filter_after_type(const MyVector<Locatar>& list, const string& tp);

    static MyVector <Locatar> filter_after_surface(const MyVector<Locatar>& list, double minimum_surface);

    static MyVector <Locatar> sort_after_name(const MyVector<Locatar>& list);

    static MyVector <Locatar> sort_after_surface(const MyVector<Locatar>& list);

    static MyVector <Locatar> sort_after_type_and_surface(const MyVector<Locatar>& list);
};

#endif //ADMINISTRATORBLOC_SERVICE_LOCATARI_H