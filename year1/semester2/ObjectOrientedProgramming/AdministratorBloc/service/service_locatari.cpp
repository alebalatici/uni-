#include "service_locatari.h"

#include <cstring>

#include "../domain/validator.h"

void ServiceLocatari::add_locatar(int apartament, const string nume, double suprafata, const string tip) {
    try {
         Locatar l{apartament, nume, suprafata, tip};
         val.validate(l);
         repo.add_locatar(l);
    }
    catch (const ValidationException& e) {
        throw ServiceException(e.get_message());
    }
    catch (const RepoException& e) {
        throw ServiceException(e.get_message());
    }

}

Locatar& ServiceLocatari::find_locatar(int numar_apartament) {
    try {
        Locatar& l = repo.find_locatar(numar_apartament);
        return l;
    }
    catch (const RepoException& e) {
        throw ServiceException(e.get_message());
    }
}

void ServiceLocatari::delete_locatar(int numar_apartament) {
    try {
        repo.delete_locatar(numar_apartament);
    }
    catch (const RepoException& e) {
        throw ServiceException(e.get_message());
    }
}

void ServiceLocatari::modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string tip_nou) {
    try {
        Locatar l{numar_apartament, nume_nou, suprafata_noua, tip_nou};
        val.validate(l);
        repo.modify_locatar(numar_apartament, nume_nou, suprafata_noua, tip_nou);
    }
    catch (const RepoException& e) {
        throw ServiceException(e.get_message());
    }
    catch (const ValidationException& e) {
        throw ServiceException(e.get_message());
    }
}

const vector <Locatar>& ServiceLocatari::get_all_locatari() const {
    return repo.get_all_locatari();
}

int ServiceLocatari::count_vowels(const string& word) {
    int count = 0;
    for (auto letter: word) {
        if (string("aeiouAEIOU").find(letter) != string::npos) {
            count++;
        }
    }
    return count;
}

vector <Locatar> ServiceLocatari::filter_after_type(const vector<Locatar>& list, const string& tip) {
    vector<Locatar> filtered_list;
    for (const auto &l : list) {
        if (l.get_tip() == tip) {
            filtered_list.push_back(l);
        }
    }
    return filtered_list;
}

vector <Locatar> ServiceLocatari::filter_after_surface(const vector<Locatar>& list, double minimum_surface) {
    vector<Locatar> filtered_list;
    for (const auto &l : list) {
        if (l.get_suprafata() >= minimum_surface) {
            filtered_list.push_back(l);
        }
    }
    return filtered_list;
}

vector <Locatar> ServiceLocatari::sort_after_name(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    for (size_t i = 0; i < sorted_list.size(); i++) {
        for (size_t j = i + 1; j < sorted_list.size(); j++) {
            if (sorted_list[i].get_nume() > sorted_list[j].get_nume()) {
                std::swap(sorted_list[i], sorted_list[j]);
            }
        }
    }
    return sorted_list;
}

vector <Locatar> ServiceLocatari::sort_after_surface(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    for (size_t i = 0; i < sorted_list.size(); i++) {
        for (size_t j = i + 1; j < sorted_list.size(); j++) {
            if (sorted_list[i].get_suprafata() > sorted_list[j].get_suprafata()) {
                std::swap(sorted_list[i], sorted_list[j]);
            }
        }
    }
    return sorted_list;
}

vector <Locatar> ServiceLocatari::sort_after_type_and_surface(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    for (size_t i = 0; i < sorted_list.size(); i++) {
        for (size_t j = i + 1; j < sorted_list.size(); j++) {
            if (sorted_list[i].get_tip() > sorted_list[j].get_tip()) {
                std::swap(sorted_list[i], sorted_list[j]);
            }
            else if (sorted_list[i].get_tip() == sorted_list[j].get_tip()) {
                if (sorted_list[i].get_suprafata() > sorted_list[j].get_suprafata()) {
                    std::swap(sorted_list[i], sorted_list[j]);
                }
            }
        }
    }
    return sorted_list;
}