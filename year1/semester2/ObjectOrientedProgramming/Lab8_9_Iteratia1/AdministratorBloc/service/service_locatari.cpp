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
    copy_if(list.begin(), list.end(),
        back_inserter(filtered_list),
        [tip](const Locatar& l)
        {
            return l.get_tip() == tip;
        });
    return filtered_list;
}

vector <Locatar> ServiceLocatari::filter_after_surface(const vector<Locatar>& list, double minimum_surface) {
    vector<Locatar> filtered_list;

    copy_if(list.begin(), list.end(),
        back_inserter(filtered_list),
        [minimum_surface](const Locatar& l)
        {
            return l.get_suprafata() >= minimum_surface;
        });

    return filtered_list;
}

vector <Locatar> ServiceLocatari::sort_after_name(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    sort(sorted_list.begin(), sorted_list.end(), [](const Locatar& a, const Locatar& b)
    {
        return a.get_nume() < b.get_nume();
    });
    return sorted_list;
}

vector <Locatar> ServiceLocatari::sort_after_surface(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    sort(sorted_list.begin(), sorted_list.end(), [](const Locatar& a, const Locatar& b)
    {
       return a.get_suprafata() < b.get_suprafata();
    });
    return sorted_list;
}

vector <Locatar> ServiceLocatari::sort_after_type_and_surface(const vector<Locatar>& list) {
    vector<Locatar> sorted_list = list;
    sort(sorted_list.begin(), sorted_list.end(), [](const Locatar& a, const Locatar& b)
    {
       return a.get_tip() < b.get_tip() || a.get_tip() == b.get_tip() && a.get_suprafata() < b.get_suprafata();
    });
    return sorted_list;
}

void ServiceLocatari::list_add_notificare(int numar_apartament)
{
    try
    {
        Locatar &l = repo.find_locatar(numar_apartament);
        lista_notificare.add_notificare(l);
    }
    catch (const RepoException& e)
    {
        throw ServiceException(e.get_message());
    }
}

void ServiceLocatari::list_empty_full()
{
    lista_notificare.empty_list();
}

void ServiceLocatari::list_add_random_notificari(int number)
{
    try
    {
        lista_notificare.add_random_notificari(this->get_all_locatari(), number);
    }
    catch (const ListaNotificareException& e)
    {
        throw ServiceException(e.get_message());
    }
}

const vector<Locatar>& ServiceLocatari::list_get_all_notificari() const
{
    return lista_notificare.get_all_notificari();
}

void ServiceLocatari::list_export_to_html(const std::string& filename) const
{
    try
    {
        lista_notificare.export_to_html(filename);
    }
    catch (const ListaNotificareException& e)
    {
        throw ServiceException(e.get_message());
    }
}