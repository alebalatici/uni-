#include "repo_locatari.h"

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

const vector<Locatar>& RepoLocatari::get_all_locatari() {
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
