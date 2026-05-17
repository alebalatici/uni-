//
// Created by Alexandra on 5/16/2026.
//

#include "repo_joc.h"

void RepoJocFile::load_from_file()
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw RepoException("Could not open file");
    }
    string line;
    while (getline(fin, line))
    {
        string titlu;
        double pret;
        string platforma;
        int age_rating;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch (item_no)
                {
                    case 0: titlu = current_item; break;
                    case 1: pret = stod(current_item); break;
                    case 2: platforma = current_item; break;
                    case 3: age_rating = stoi(current_item); break;
                    default: break;
                }
                item_no++;
            }
            if (item_no != 4)
            {
                throw RepoException("Formatting error on line " + line + "\n");
            }
            Joc joc{titlu, pret, platforma, age_rating};
            RepoJoc::add_joc(joc);
        }
        catch (std::exception& e)
        {
            throw RepoException(e.what());
        }
    }
}

void RepoJocFile::save_to_file()
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        throw RepoException("Could not open file");
    }
    for (auto& joc : jocuri)
    {
        fout << joc.get_titlu() << ',' << joc.get_pret() << ',' << joc.get_platforma() << ',' << joc.get_age_rating() << '\n';
    }
}