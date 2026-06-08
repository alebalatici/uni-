//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_REPO_MELODII_H
#define MELODII_REPO_MELODII_H

#include <exception>
#include <string>
#include <utility>
#include <vector>
#include "../domain/melodie.h"
#include "../utils/file_utils.h"
using std::string;
using std::vector;
using std::vector;
class RepoException : public std::exception
{
private:
    string msg;
public:
    explicit RepoException(string  msg) : msg(std::move(msg)) {};
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); };
};

class Repo
{
public:
    virtual ~Repo() = default;
    Repo() = default;

    virtual void add_melodie(const Melodie& melodie) = 0;
    virtual void delete_melodie(int id) = 0;
    virtual void modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou) = 0;
    [[nodiscard]] virtual Melodie& find_melodie(int id) = 0;
    [[nodiscard]] virtual const vector<Melodie>& get_all_melodii() const = 0;
};

class RepoMelodii : public Repo
{
    protected:
    vector<Melodie> melodii;
    public:
    void add_melodie(const Melodie& melodie) override;
    void delete_melodie(int id) override;
    void modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou) override;
    [[nodiscard]] Melodie& find_melodie(int id) override;
    [[nodiscard]] const vector<Melodie>& get_all_melodii() const override;
};

class RepoMelodiiFile : public RepoMelodii
{
    private:
    string filename;
    void load_from_file();
    void save_to_file();
    public:
    RepoMelodiiFile(const string& _filename) : filename(_filename)
    {
        load_from_file();
    };
    void add_melodie(const Melodie& melodie) override;
    void delete_melodie(int id) override;
    void modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou) override;
    [[nodiscard]] Melodie& find_melodie(int id) override;
    [[nodiscard]] const vector<Melodie>& get_all_melodii() const override;
};

#endif //MELODII_REPO_MELODII_H
