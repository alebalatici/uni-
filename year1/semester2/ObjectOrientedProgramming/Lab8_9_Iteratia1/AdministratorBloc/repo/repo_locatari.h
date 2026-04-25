#ifndef ADMINISTRATORBLOC_REPO_LOCATARI_H
#define ADMINISTRATORBLOC_REPO_LOCATARI_H
#include <utility>
#include <vector>
#include <algorithm>
#include <exception>
#include "../domain/locatar.h"
using std::vector;
using std::find_if;

class RepoException : public std::exception {
    string msg;
public:
    RepoException(string msg) : msg(std::move(msg)) {

    }
    [[nodiscard]] string get_message() const {
        return msg;
    }
};

class RepoLocatari {
private:
    vector<Locatar> locatari;
public:
    RepoLocatari(const Locatar &ot) = delete;
    RepoLocatari() = default;

    void add_locatar(const Locatar &loc);

    void delete_locatar(int numar_apartament);

    Locatar& find_locatar(int numar_apartament);

    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou);

    const vector<Locatar> &get_all_locatari();
};

#endif //ADMINISTRATORBLOC_REPO_LOCATARI_H