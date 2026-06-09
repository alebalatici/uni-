//
// Created by Alexandra on 5/10/2026.
//

#include "repo_produs.h"

#include "../utils/file_utils.h"

void RepoProdus::add_produs(const Produs& produs)
{
    auto it = find_if(produse.begin(), produse.end(),
        [produs](const Produs& p)
        {
            return p.get_id() == produs.get_id();
        });
    if (it != produse.end())
    {
        throw RepoException("Produs already exists\n");
    }
    produse.push_back(produs);
}

void RepoProdus::delete_produs(int id)
{
    Produs& produs = find_produs(id);
    for (auto it = produse.begin(); it != produse.end(); ++it)
    {
        if (*it == produs)
        {
            produse.erase(it);
            return;
        }
    }
}

void RepoProdus::modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou)
{
    Produs& produs = find_produs(id);
    produs.set_nume(nume_nou);
    produs.set_tip(tip_nou);
    produs.set_pret(pret_nou);
}

Produs& RepoProdus::find_produs(int id)
{
    auto it = find_if(produse.begin(), produse.end(),
        [id](const Produs& p)
        {
            return p.get_id() == id;
        });
    if (it == produse.end())
    {
        throw RepoException("Produs does not exist\n");
    }
    return *it;
}

const vector<Produs>& RepoProdus::get_all_produse() const
{
    return produse;
}

void RepoProdusFile::load_from_file()
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw RepoException("Cannot open file\n");
    }
    string line;
    while (getline(fin, line))
    {
        FileUtils::sanitize(line);
        int id;
        string nume;
        string tip;
        double pret;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch(item_no)
                {
                    case 0: id = stoi(current_item); break;
                    case 1: nume = current_item; break;
                    case 2: tip = current_item; break;
                    case 3: pret = stod(current_item); break;
                    default: break;
                }
                item_no++;
            }
            if (item_no != 4)
            {
                throw RepoException("Eoare de formatare pe linia" + line + "\n");
            }

            Produs produs{id, nume, tip, pret};
            RepoProdus::add_produs(produs);
        }
        catch (std::exception& e)
        {
            throw RepoException(e.what());
        }
    }
}

void RepoProdusFile::save_to_file()
{
    ofstream fout(this->filename);
    if (!fout.is_open())
    {
        throw RepoException("Cannot open file\n");
    }
    for (auto &produs : produse)
    {
        fout << produs.get_id() << ',' << produs.get_nume() << ',' << produs.get_tip() << ',' << produs.get_pret() << '\n';
    }
}

void RepoProdusFile::add_produs(const Produs& produs)
{
    RepoProdus::add_produs(produs);
    save_to_file();
}

void RepoProdusFile::delete_produs(int id)
{
    RepoProdus::delete_produs(id);
    save_to_file();
}

void RepoProdusFile::modify_produs(int id, const string& nume_nou, const string& tip_nou, double pret_nou)
{
    RepoProdus::modify_produs(id, nume_nou, tip_nou, pret_nou);
    save_to_file();
}

Produs& RepoProdusFile::find_produs(int id)
{
    return RepoProdus::find_produs(id);
}

const vector<Produs>& RepoProdusFile::get_all_produse() const
{
    return RepoProdus::get_all_produse();
}