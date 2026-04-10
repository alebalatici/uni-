#ifndef ADMINISTRATORBLOC_REPO_LOCATARI_H
#define ADMINISTRATORBLOC_REPO_LOCATARI_H
#include <utility>
#include <vector>
#include <exception>
#include "../domain/locatar.h"
#include "../vector/myvector.h"
using std::vector;

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
    MyVector<Locatar> locatari;
public:
    RepoLocatari(const Locatar &ot) = delete;
    RepoLocatari() = default;

    void add_locatar(const Locatar &loc);

    void delete_locatar(int numar_apartament);

    Locatar& find_locatar(int numar_apartament);

    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou);

    const MyVector<Locatar>& get_all_locatari();
};

#endif //ADMINISTRATORBLOC_REPO_LOCATARI_H