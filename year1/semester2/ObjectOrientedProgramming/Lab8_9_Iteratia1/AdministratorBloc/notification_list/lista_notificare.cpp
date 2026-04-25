#include "lista_notificare.h"



void ListaNotificare::add_notificare(const Locatar &loc)
{
    this->lista_notificari.push_back(loc);
}

void ListaNotificare::empty_list()
{
    this->lista_notificari.clear();
}

void ListaNotificare::add_random_notificari(vector<Locatar> original_notificari, int number)
{
    if (number > original_notificari.size())
    {
        throw ListaNotificareException("Prea multe argumente\n");
    }

    shuffle(original_notificari.begin(), original_notificari.end(), std::default_random_engine {std::random_device{}()});
    int count = 0;
    while (count < number && !original_notificari.empty())
    {
        lista_notificari.push_back(original_notificari.back());
        original_notificari.pop_back();
        count++;
    }
}

const vector<Locatar>& ListaNotificare::get_all_notificari() const
{
    return this->lista_notificari;
}

void ListaNotificare::export_to_html(const std::string &filename) const
{
    std::ofstream out(filename);

    if (!out.is_open())
    {
        throw ListaNotificareException("Nu s-a putut deschide fisierul pentru export\n");
    }

    /*
    out << "<!DOCTYPE html>\n";
    out << "<html>\n<head>\n";
    out << "<title>Lista Notificari</title>\n";

    out << "<style>\n";
    out << "table { border-collapse: collapse; width: 100%; }\n";
    out << "th, td { border: 1px solid black; padding: 8px; text-align: left; }\n";
    out << "th { background-color: #f2f2f2; }\n";
    out << "</style>\n";

    out << "</head>\n<body>\n";

    out << "<h1>Lista Notificari</h1>\n";

    out << "<table>\n";
    out << "<tr><th>Apartament</th><th>Nume</th><th>Suprafata</th><th>Tip</th></tr>\n";

    for (const auto& loc : lista_notificari) {
        out << "<tr>";
        out << "<td>" << loc.get_apartment() << "</td>";
        out << "<td>" << loc.get_nume() << "</td>";
        out << "<td>" << loc.get_suprafata() << "</td>";
        out << "<td>" << loc.get_tip() << "</td>";
        out << "</tr>\n";
    }

    out << "</table>\n";
    out << "</body>\n</html>\n";
    */


    out << "<!DOCTYPE html>\n";
    out << "<html>\n<head>\n";
    out << "<title>Lista Notificari</title>\n";

    // CSS
    out << "<style>\n";
    out << "table { border-collapse: collapse; width: 100%; }\n";
    out << "th, td { border: 1px solid black; padding: 8px; text-align: left; }\n";
    out << "th { background-color: #ffb6c1; }\n"; // roz pastel
    out << "tr:hover { background-color: #f5f5f5; }\n";
    out << "</style>\n";

    out << "</head>\n<body>\n";

    out << "<h1>Lista Notificari</h1>\n";

    out << "<table>\n";
    out << "<tr>\n";
    out << "<th>Apartament</th>\n";
    out << "<th>Nume</th>\n";
    out << "<th>Suprafata</th>\n";
    out << "<th>Tip</th>\n";
    out << "</tr>\n";

    for (const auto& loc : lista_notificari) {
        out << "<tr>\n";
        out << "<td>" << loc.get_apartment() << "</td>\n";
        out << "<td>" << loc.get_nume() << "</td>\n";
        out << "<td>" << loc.get_suprafata() << "</td>\n";
        out << "<td>" << loc.get_tip() << "</td>\n";
        out << "</tr>\n";
    }

    out << "</table>\n";

    out << "</body>\n</html>\n";



    /*
    out << "<!DOCTYPE html>\n";
    out << "<html>\n<head>\n";
    out << "<meta charset='UTF-8'>\n";
    out << "<title>Lista Notificari</title>\n";

    out << "<style>\n";
    out << "body { font-family: Arial, sans-serif; margin: 20px; background-color: #fafafa; }\n";

    out << "h1 { text-align: center; color: #333; }\n";

    out << "table {\n";
    out << "  width: 80%;\n";
    out << "  margin: auto;\n";
    out << "  border-collapse: collapse;\n";
    out << "  box-shadow: 0px 0px 10px rgba(0,0,0,0.1);\n";
    out << "  background: white;\n";
    out << "  border-radius: 8px;\n";
    out << "  overflow: hidden;\n";
    out << "}\n";

    out << "th {\n";
    out << "  background-color: #ffb6c1;\n";
    out << "  color: black;\n";
    out << "  padding: 12px;\n";
    out << "}\n";

    out << "td {\n";
    out << "  padding: 10px;\n";
    out << "  border-bottom: 1px solid #ddd;\n";
    out << "}\n";

    out << "tr:hover {\n";
    out << "  background-color: #f5f5f5;\n";
    out << "}\n";

    out << "</style>\n";
    out << "</head>\n<body>\n";

    out << "<h1>Lista Notificari</h1>\n";
    */
}