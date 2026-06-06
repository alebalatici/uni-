//
// Created by Alexandra on 5/18/2026.
//

#include "repo_jucatori.h"

void RepoJucatoriFile::load_from_file()
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw RepoException("Cannot open file");
    }

    string line;
    while (getline(fin, line))
    {
        FileUtils::sanitize(line);
        string nume;
        string tara;
        int numar_puncte;
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
                    case 0: nume = current_item; break;
                    case 1: tara = current_item; break;
                    case 2: numar_puncte = stoi(current_item); break;
                    case 3: rank = stoi(current_item); break;
                    default: break;
                }
                item_no++;
            }
            if (item_no != 4)
            {
                throw RepoException("Formatting error on line" + line);
            }
            Jucator jucator{nume, tara, numar_puncte, rank};
            RepoJucatori::add_jucator(jucator);
        }
        catch (std::exception& e)
        {
            throw RepoException(e.what());
        }
    }
}