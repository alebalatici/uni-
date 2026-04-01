#ifndef ADMINISTRATORBLOC_SERVICE_LOCATARI_H
#define ADMINISTRATORBLOC_SERVICE_LOCATARI_H
#include <string>
#include "../domain/locatar.h"
#include "../repo/repo_locatari.h"
#include "../domain/validator.h"
using std::string;

class ServiceException : public std::exception {
    string msg;
public:
    ServiceException(string msg) : msg{msg} {

    }
    string get_msg() {
        return msg;
    }
};

class ServiceLocatari {
private:
    RepoLocatari& repo;
    ValidatorLocatar& val;
    vector<vector<Locatar>> undo_list;
public:
    ServiceLocatari(RepoLocatari& repo, ValidatorLocatar& val): repo{repo}, val{val} {}
    ServiceLocatari(const ServiceLocatari& ot) = delete;
    ServiceLocatari() = delete;

    void add_locatar(int apartament, const string nume, double suprafata, const string tip);

    Locatar& find_locatar(int numar_apartament);

    void delete_locatar(int numar_apartament);

    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string tip_nou);

    const vector <Locatar>& get_all_locatari() const;

    static int count_vowels(const string& word);

    static vector <Locatar> filter_after_type(const vector<Locatar>& list, const string& tp);

    static vector <Locatar> filter_after_surface(const vector<Locatar>& list, double minimum_surface);

    static vector <Locatar> sort_after_name(const vector<Locatar>& list);

    static vector <Locatar> sort_after_surface(const vector<Locatar>& list);

    static vector <Locatar> sort_after_type_and_surface(const vector<Locatar>& list);
};

#endif //ADMINISTRATORBLOC_SERVICE_LOCATARI_H