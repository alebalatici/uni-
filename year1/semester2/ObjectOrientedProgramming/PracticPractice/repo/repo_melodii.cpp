//
// Created by Alexandra on 5/9/2026.
//

#include <algorithm>
#include <fstream>
#include "repo_melodii.h"
#include <sstream>
#include <exception>
using std::find_if;
using std::ifstream;
using std::ofstream;
using std::stringstream;
void RepoMelodii::add_melodie(const Melodie& melodie)
{
    auto it = find_if(melodii.begin(), melodii.end(),
        [melodie](const Melodie& m)
        {
            return m.get_id() == melodie.get_id();
        });

    if (it != melodii.end())
    {
        throw RepoException("Melodia exista deja\n");
    }
    melodii.push_back(melodie);
}

Melodie& RepoMelodii::find_melodie(int id)
{
    auto it = find_if(melodii.begin(), melodii.end(),
        [id](const Melodie& m)
        {
            return m.get_id() == id;
        });

    if (it == melodii.end())
    {
        throw RepoException("Melodia nu exista\n");
    }
    return *it;
}

void RepoMelodii::delete_melodie(int id)
{
    Melodie& melodie = find_melodie(id);
    for (auto it = melodii.begin(); it != melodii.end(); ++it)
    {
        if (*it == melodie)
        {
            melodii.erase(it);
            return;
        }
    }
}

void RepoMelodii::modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou)
{
    Melodie& melodie = find_melodie(id);
    melodie.set_titlu(titlu_nou);
    melodie.set_artist(artist_nou);
    melodie.set_rank(rank_nou);
}

const vector<Melodie>& RepoMelodii::get_all_melodii() const
{
    return melodii;
}

void RepoMelodiiFile::load_from_file()
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw RepoException("Eroare la deschiderea fisierului\n");
    }

    string line;
    while (getline(file, line))
    {
        FileUtils::sanitize(line);
        int id;
        string titlu, artist;
        int rank;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch (item_no)
                {
                    case 0:
                        id = stoi(current_item);
                        break;
                    case 1:
                        titlu = current_item;
                        break;
                    case 2:
                        artist = current_item;
                        break;
                    case 3:
                        rank = stoi(current_item);
                        break;
                    default:
                        break;
                }
                item_no++;
            }
            if (item_no != 4)
            {
                throw RepoException("Eroare de formatare pe linia "  + line + "\n");
            }
            Melodie melodie{id, titlu, artist, rank};
            RepoMelodii::add_melodie(melodie);
        }
        catch (std::exception& e)
        {
            throw RepoException(e.what());
        }
    }
}

void RepoMelodiiFile::save_to_file()
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        throw RepoException("Eroare la deschiderea fisierului\n");
    }
    for (auto &melodie : melodii)
    {
        fout << melodie.get_id() << ',' << melodie.get_titlu() << ',' << melodie.get_artist() << ',' << melodie.get_rank() << '\n';
    }
}

void RepoMelodiiFile::add_melodie(const Melodie& melodie)
{
    RepoMelodii::add_melodie(melodie);
    save_to_file();
}

void RepoMelodiiFile::delete_melodie(int id)
{
    RepoMelodii::delete_melodie(id);
    save_to_file();
}

void RepoMelodiiFile::modify_melodie(int id, const string& titlu_nou, const string& artist_nou, int rank_nou)
{
    RepoMelodii::modify_melodie(id, titlu_nou, artist_nou, rank_nou);
    save_to_file();
}

Melodie& RepoMelodiiFile::find_melodie(int id)
{
    return RepoMelodii::find_melodie(id);
}

const vector<Melodie>& RepoMelodiiFile::get_all_melodii() const
{
    return RepoMelodii::get_all_melodii();
}