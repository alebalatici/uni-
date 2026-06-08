//
// Created by Alexandra on 5/9/2026.
//

#include "melodie.h"

int Melodie::get_id() const
{
    return id;
}

string Melodie::get_titlu() const
{
    return titlu;
}

string Melodie::get_artist() const
{
    return artist;
}

int Melodie::get_rank() const
{
    return rank;
}

void Melodie::set_titlu(const string& titlu_nou)
{
    titlu = titlu_nou;
}

void Melodie::set_artist(const string& artist_nou)
{
    artist = artist_nou;
}

void Melodie::set_rank(int rank_nou)
{
    rank = rank_nou;
}

std::ostream& operator<<(std::ostream& os, const Melodie& melodie)
{
    os << "Id: " << melodie.get_id() << " | Titlu: " <<  melodie.get_titlu() << " | Artist: " << melodie.get_artist() << " | Rank: " << melodie.get_rank();
    return os;
}