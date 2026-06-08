//
// Created by Alexandra on 5/9/2026.
//

#ifndef MELODII_MELODIE_H
#define MELODII_MELODIE_H

#include <iostream>
#include <string>
#include <ostream>
using std::string;
class Melodie {
private:
    int id = 0;
    string titlu;
    string artist;
    int rank = 0;
public:
    Melodie(int _id, const string& _titlu, const string& _artist, int rank) : id{_id}, titlu{_titlu}, artist{_artist}, rank{rank} {}
    Melodie(const Melodie &ot) : id{ot.id}, titlu{ot.titlu}, artist{ot.artist}, rank{ot.rank} {}

    bool operator==(const Melodie &other) const
    {
        return other.id == id && other.titlu == titlu && other.artist == artist && other.rank == rank;
    }

    friend std::ostream &operator<<(std::ostream &os, const Melodie &melodie);
    [[nodiscard]] int get_id() const;
    [[nodiscard]] string get_titlu() const;
    [[nodiscard]] string get_artist() const;
    [[nodiscard]] int get_rank() const;

    void set_titlu(const string& titlu_nou);
    void set_artist(const string& artist_nou);
    void set_rank(int rank_nou);
};

#endif //MELODII_MELODIE_H