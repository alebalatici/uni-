#include "service_locatari.h"

#include "../domain/validator.h"

void ServiceLocatari::add_locatar(int apartament, const string& nume, double suprafata, const string& tip) {
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

void ServiceLocatari::modify_locatar(int numar_apartament, const string& nume_nou, double suprafata_noua, const string& tip_nou) {
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

const MyVector <Locatar>& ServiceLocatari::get_all_locatari() const {
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

MyVector <Locatar> ServiceLocatari::filter_after_type(const MyVector<Locatar>& list, const string& tip) {
    MyVector<Locatar> filtered_list;
    for (const auto &l : list) {
        if (l.get_tip() == tip) {
            filtered_list.push_back(l);
        }
    }
    return filtered_list; }

MyVector <Locatar> ServiceLocatari::filter_after_surface(const MyVector<Locatar>& list, double minimum_surface) {
    MyVector<Locatar> filtered_list;
    for (const auto &l : list) {
        if (l.get_suprafata() >= minimum_surface) {
            filtered_list.push_back(l);
        }
    }
    return filtered_list; }

bool cmp_name(const Locatar& a, const Locatar& b)
{
    return a.get_nume() < b.get_nume();
}

MyVector <Locatar> ServiceLocatari::sort_after_name(const MyVector<Locatar>& list) {
    MyVector<Locatar> sorted_list = list;
    std::sort(sorted_list.begin(), sorted_list.end(), cmp_name);
    return sorted_list; }

MyVector <Locatar> ServiceLocatari::sort_after_surface(const MyVector<Locatar>& list) {
    MyVector<Locatar> sorted_list = list;
    std::sort(sorted_list.begin(), sorted_list.end(), [](const Locatar& a, const Locatar& b)
    {
       return a.get_suprafata() < b.get_suprafata();
    });
    return sorted_list; }

MyVector <Locatar> ServiceLocatari::sort_after_type_and_surface(const MyVector<Locatar>& list) {
    MyVector<Locatar> sorted_list = list;
    std::sort(sorted_list.begin(), sorted_list.end(), [](const Locatar& a, const Locatar& b)
    {
       return a.get_tip() < b.get_tip() || a.get_tip() == b.get_tip() && a.get_suprafata() < b.get_suprafata();
    });
    return sorted_list; }