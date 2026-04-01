#include "repo_locatari.h"

void RepoLocatari::add_locatar(const Locatar &loc) {
    for (const Locatar &l: locatari) {
        if (l.get_apartment() == loc.get_apartment()) {
            throw RepoException("Locatar already exists");
        }
    }
    locatari.push_back(loc);
}

const vector<Locatar>& RepoLocatari::get_all_locatari() {
    return locatari;
}

Locatar& RepoLocatari::find_locatar(int numar_apartament) {
   for (auto& l: locatari) {
       if (l.get_apartment() == numar_apartament) {
           return l;
       }
   }
    throw RepoException("Locatar does not exist");
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
