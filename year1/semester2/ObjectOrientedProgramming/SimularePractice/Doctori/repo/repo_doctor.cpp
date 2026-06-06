//
// Created by Alexandra on 5/17/2026.
//

#include "repo_doctor.h"

void RepoDoctorFile::load_from_file()
{
    ifstream fin(filename);
    if (!fin.is_open())
    {
        throw RepoException("Could not open file");
    }
    string line;
    while (getline(fin, line))
    {
        string cnp;
        string nume;
        string prenume;
        string sectie;
        int concediu;

        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch (item_no)
                {
                    case 0: cnp = current_item; break;
                    case 1: nume = current_item; break;
                    case 2: prenume = current_item; break;
                    case 3: sectie = current_item; break;
                    case 4: concediu = stoi(current_item); break;
                    default: break;
                }
                item_no++;
            }
            if (item_no != 5)
            {
                throw RepoException("Formatting error on line " + line);
            }
            Doctor doctor{cnp, nume, prenume, sectie, concediu};
            RepoDoctor::add_doctor(doctor);
        }
        catch (std::exception& e)
        {
            throw RepoException(e.what());
        }
    }
}

void RepoDoctorFile::save_to_file()
{
    ofstream fout(filename);
    if (!fout.is_open())
    {
        throw RepoException("Could not open file");
    }
    for (auto &d : doctori)
    {
        fout << d.get_cnp() << ',' << d.get_nume() << ',' << d.get_prenume() << ',' << d.get_sectie() << ',' << d.get_concediu() << '\n';
    }
}