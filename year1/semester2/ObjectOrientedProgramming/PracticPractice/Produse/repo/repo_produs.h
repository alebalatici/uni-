//
// Created by Alexandra on 5/10/2026.
//

#ifndef PRODUSE_REPO_PRODUS_H
#define PRODUSE_REPO_PRODUS_H

#include <utility>
#include <vector>
#include <exception>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "../domain/produs.h"
#include "../utils/file_utils.h"
using std::vector;
using std::exception;
using std::find_if;
using std::ifstream;
using std::ofstream;
using std::stringstream;
class RepoException : public exception
{
private:
    string msg;
public:
    explicit RepoException(string  msg) : msg{std::move(msg)} {}
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
};

class Repo {
public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_produs(const Produs& produs) = 0;
    virtual void delete_produs(int id) = 0;
    virtual void modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou) = 0;
    [[nodiscard]] virtual Produs& find_produs(int id) = 0;
    [[nodiscard]] virtual const vector<Produs>& get_all_produse() const = 0;
};

class RepoProdus : public Repo
{
    protected:
    vector<Produs> produse;
    public:
    void add_produs(const Produs& produs) override;
    void delete_produs(int id) override;
    void modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou) override;
    [[nodiscard]] Produs& find_produs(int id) override;
    [[nodiscard]] const vector<Produs>& get_all_produse() const override;
};

class RepoProdusFile : public RepoProdus
{
    private:
    string filename;
    void load_from_file();
    void save_to_file();
    public:
    RepoProdusFile(string _filename) : filename{std::move(_filename)}
    {
        load_from_file();
    }

    void add_produs(const Produs& produs) override;
    void delete_produs(int id) override;
    void modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou) override;
    [[nodiscard]] Produs& find_produs(int id) override;
    [[nodiscard]] const vector<Produs>& get_all_produse() const override;
};

#endif //PRODUSE_REPO_PRODUS_H
