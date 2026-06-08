//
// Created by Alexandra on 5/9/2026.
//

#include "service_melodii.h"

void ServiceMelodii::add_melodie(int id, const string& titlu, const string& artist, int rank)
{
    try
    {
        Melodie melodie{id, titlu, artist, rank};
        val.validate(melodie);
        repo.add_melodie(melodie);
        notify();
    }
    catch (std::exception& e)
    {
        throw ServiceException{e.what()};
    }
}

void ServiceMelodii::delete_melodie(int id)
{
    try
    {
        repo.delete_melodie(id);
        notify();
    }
    catch (std::exception& e)
    {
        throw ServiceException{e.what()};
    }
}

void ServiceMelodii::modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou)
{
    try
    {
        Melodie melodie{id, titlu_nou, artist_nou, rank_nou};
        val.validate(melodie);
        repo.modify_melodie(id, titlu_nou, artist_nou, rank_nou);
        notify();
    }
    catch (std::exception& e)
    {
        throw ServiceException{e.what()};
    }
}

Melodie& ServiceMelodii::find_melodie(int id)
{
    try
    {
        return repo.find_melodie(id);
    }
    catch (std::exception& e)
    {
        throw ServiceException{e.what()};
    }
}

const vector<Melodie>& ServiceMelodii::get_all_melodii() const
{
    return repo.get_all_melodii();
}

vector<Melodie> ServiceMelodii::sort_by_rank(const vector<Melodie>& melodii)
{
    vector<Melodie> sorted_melodii = melodii;
    sort(sorted_melodii.begin(), sorted_melodii.end(),
        [](const Melodie& a, const Melodie& b)
    {
            return a.get_rank() < b.get_rank();
    });
    return sorted_melodii;
}

vector<int>ServiceMelodii::get_rank_frequencies(const vector<Melodie>& melodii)
{
    vector<int> rank_frequencies(11, 0);
    for (auto& melodie : melodii)
    {
        rank_frequencies[melodie.get_rank()]++;
    }
    return rank_frequencies;
}

map<string, int> ServiceMelodii::get_artist_song_count(const vector<Melodie>& melodii)
{
    map<string, int> artist_song_count;
    for (auto& melodie : melodii)
    {
        artist_song_count[melodie.get_artist()]++;
    }
    return artist_song_count;
}