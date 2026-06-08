//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_SERVICE_MELODII_H
#define MELODII_SERVICE_MELODII_H

#include <exception>
#include <utility>
#include <algorithm>
#include <map>
#include "../domain/validator.h"
#include "../repo/repo_melodii.h"
#include "../observer/observer.h"

using std::sort;
using std::map;
class ServiceException : public std::exception
{
private:
    string msg;
public:
    explicit ServiceException(string  msg) : msg{std::move(msg)} {};
    [[nodiscard]] const char* what() const noexcept override { return msg.c_str(); }
};

class ServiceMelodii : public Observable {
    private:
    Repo& repo;
    Validator& val;
    public:
    ServiceMelodii(Repo& _repo, Validator& _val) : repo{_repo}, val {_val} {};
    ServiceMelodii(const ServiceMelodii &ot) = delete;
    ServiceMelodii() = delete;

    void add_melodie(int id, const string& titlu, const string& artist, int rank);
    void delete_melodie(int id);
    void modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou);
    [[nodiscard]] Melodie& find_melodie(int id);
    [[nodiscard]] const vector<Melodie>& get_all_melodii() const;
    static vector<Melodie> sort_by_rank(const vector<Melodie>& melodii);
    static vector<int> get_rank_frequencies(const vector<Melodie>& melodii);
    static map<string, int> get_artist_song_count(const vector<Melodie>& melodii);
};

#endif //MELODII_SERVICE_MELODII_H
