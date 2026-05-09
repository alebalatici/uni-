#include "repo_locatari.h"

#include <filesystem>

void RepoLocatari::add_locatar(const Locatar &loc) {
    auto it = find_if(locatari.begin(), locatari.end(),
        [loc](const Locatar& l)
        {
            return l.get_apartment() == loc.get_apartment();
        });

    if (it != locatari.end())
    {
        throw RepoException("Locatar already exists\n");
    }

    locatari.push_back(loc);
}

const vector<Locatar>& RepoLocatari::get_all_locatari() const {
    return locatari;
}

Locatar& RepoLocatari::find_locatar(int numar_apartament) {
    auto it = find_if(locatari.begin(), locatari.end(),
        [numar_apartament](const Locatar& loc)
        {
            return loc.get_apartment() == numar_apartament;
        });
    if (it != locatari.end())
    {
        return *it;
    }
    throw RepoException("Locatar does not exist\n");
}

void RepoLocatari::delete_locatar(int numar_apartament) {
    Locatar& loc = find_locatar(numar_apartament);
    for (auto it = locatari.begin(); it != locatari.end(); ++it) {
        if (*it == loc) {
            locatari.erase(it);
            return;
        }
    }
}

void RepoLocatari::modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou) {
    Locatar& loc = find_locatar(numar_apartament);
    loc.set_nume(nume_nou);
    loc.set_suprafata(suprafata_noua);
    loc.set_tip(tip_nou);
}

void RepoLocatariFile::load_from_file()
{
    ifstream file(this->filename);
    if (!file.is_open())
    {
        throw RepoException("Nu s-a putut deschide fisierul " + filename);
    }

    string line;
    while (getline(file, line))
    {
        FileUtils::sanitize(line);
        int apartament = 0;
        string nume = "", tip = "";
        double suprafata = 0.0;
        stringstream linestream(line);
        string current_item;
        int item_no = 0;
        try
        {
            while (getline(linestream, current_item, ','))
            {
                switch (item_no)
                {
                    case 0: apartament = std::stoi(current_item); break;
                    case 1: nume = current_item; break;
                    case 2: suprafata = std::stod(current_item); break;
                    case 3: tip = current_item; break;
                    default: break;
                }
                item_no++;
            }

            if (item_no != 4)
                throw RepoException("Eroare de formatare pe linia: " + line);

            Locatar l = Locatar{apartament, nume, suprafata, tip};
            RepoLocatari::add_locatar(l);
        }
        catch(const std::exception&)
        {
            throw RepoException("Eroare de formatare pe linia: " + line);
        }
    }
}

void RepoLocatariFile::save_to_file()
{
    ofstream file(this->filename);
    if (!file.is_open())
    {
        throw RepoLocatariFile("Nu sa putut deschide fisierul " + filename);
    }
    for (auto& locatar : locatari)
    {
        file << locatar.get_apartment() << ',' << locatar.get_nume() << ',' << locatar.get_suprafata() << ',' << locatar.get_tip() << '\n';

    }
}

void RepoLocatariFile::add_locatar(const Locatar &loc)
{
    RepoLocatari::add_locatar(loc);
    save_to_file();
}

void RepoLocatariFile::delete_locatar(int numar_apartament)
{
    RepoLocatari::delete_locatar(numar_apartament);
    save_to_file();
}

Locatar& RepoLocatariFile::find_locatar(int numar_apartament)
{
    return RepoLocatari::find_locatar(numar_apartament);
}

void RepoLocatariFile::modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou)
{
    RepoLocatari::modify_locatar(numar_apartament, nume_nou, suprafata_noua, tip_nou);
    save_to_file();
}

const vector<Locatar>& RepoLocatariFile::get_all_locatari() const
{
    return RepoLocatari::get_all_locatari();
}