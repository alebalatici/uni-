#ifndef ADMINISTRATORBLOC_LISTA_NOTIFICARE_H
#define ADMINISTRATORBLOC_LISTA_NOTIFICARE_H

#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include "../domain/locatar.h"
using std::vector;
using std::shuffle;

class ListaNotificareException : public std::exception
{
    string msg;
    public:
    ListaNotificareException(string message) : msg(message)
    {

    }
    [[nodiscard]] string get_message() const
    {
        return msg;
    }
};

class ListaNotificare {
    private:
        std::vector<Locatar> lista_notificari;

    public:
    ListaNotificare() = default;
    void add_notificare(const Locatar &loc);
    void empty_list();
    void add_random_notificari(vector<Locatar> original_notificari, int number);
    const vector<Locatar>& get_all_notificari() const;
    void export_to_html(const std::string &filename) const;
};

#endif //ADMINISTRATORBLOC_LISTA_NOTIFICARE_H
