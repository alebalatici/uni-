#ifndef ADMINISTRATORBLOC_REPO_LOCATARI_H
#define ADMINISTRATORBLOC_REPO_LOCATARI_H
#include <utility>
#include <vector>
#include <algorithm>
#include <exception>
#include <string>
#include <sstream>
#include <fstream>
#include "../domain/locatar.h"
#include "../utils/file_utils.h"
using std::vector;
using std::find_if;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;

class RepoException : public std::exception {
    string msg;
public:
    RepoException(string message) : msg(std::move(message)) {

    }
    [[nodiscard]] string get_message() const {
        return msg;
    }
};

class Repo
{
    public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_locatar(const Locatar &loc) = 0;
    virtual void delete_locatar(int numar_apartament) = 0;
    virtual Locatar& find_locatar(int numar_apartament) = 0;
    virtual void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou) = 0;
    [[nodiscard]] virtual const vector<Locatar> &get_all_locatari() const = 0;
};

class RepoLocatari : public Repo {
protected:
    vector<Locatar> locatari;
public:
    void add_locatar(const Locatar &loc) override;
    void delete_locatar(int numar_apartament) override;
    Locatar& find_locatar(int numar_apartament) override;
    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou) override;
    [[nodiscard]] const vector<Locatar> &get_all_locatari() const override;
};

class RepoLocatariFile : public RepoLocatari
{
private:
    string filename;
    void load_from_file();
    void save_to_file();
public:

    RepoLocatariFile(string file) :RepoLocatari(), filename{ std::move(file) }
    {
        load_from_file();
    }

    void add_locatar(const Locatar &loc) override;
    void delete_locatar(int numar_apartament) override;
    Locatar& find_locatar(int numar_apartament) override;
    void modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou) override;
    [[nodiscard]] const vector<Locatar> &get_all_locatari() const override;
};

#endif //ADMINISTRATORBLOC_REPO_LOCATARI_H