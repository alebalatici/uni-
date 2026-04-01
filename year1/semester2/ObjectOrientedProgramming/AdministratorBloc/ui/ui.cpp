#include "ui.h"

using std::cin;
using std::cout;
using std::numeric_limits;

bool Console::YesNoMenu() {
    while (true) {
        cout << "Continuati? (Yes/No): ";
        string option;
        cin >> option;

        if (option == "Yes" || option == "yes"  || option == "Y" || option == "y") {
            return true;
        }
        if (option == "No" || option == "no" || option == "N" || option == "n") {
            return false;
        }
        cout << "Optiune invalida!\n";
    }
}

void Console::print_menu() {
    cout << "1. Afiseaza toti locatarii\n";
    cout << "2. Adauga un locatar\n";
    cout << "3. Sterge un locatar\n";
    cout << "4. Modifica un locatar\n";
    cout << "5. Cauta un apartament dupa numar\n";
    cout << "6. Filtreaza dupa tip\n";
    cout << "7. Filtreaza dupa suprafata\n";
    cout << "8. Sorteaza dupa nume proprietar\n";
    cout << "9. Sorteaza dupa suprafata\n";
    cout << "10. Sorteaza dupa tip apartament si suprafata\n";
    cout << "11. Exit\n";
}

void Console::print_all_locatari(const vector<Locatar>& locatari) {
    if (locatari.empty()) {
        cout << "Lista este goala!\n";
    }
    else {
        for (const auto & locatar : locatari) {
            cout << locatar << "\n";
        }
    }
}

void Console::add_locatar_ui() const {
    try {
        int numar_apartament;
        while (true) {
            cout << "Introduceti numarul apartamentului locatarului:\n>>>";
            cin >> numar_apartament;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }

        string nume;
        cout << "Introduceti numele locatarului:\n>>>";
        cin >> nume;

        double suprafata;
        while (true) {
            cout << "Introduceti suprafata apartamentului locatarului:\n>>>";
            cin >> suprafata;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }

        string tip;
        cout << "Introduceti tipul apartamentului locatarului:\n>>>";
        cin >> tip;
        srv.add_locatar(numar_apartament, nume, suprafata, tip);
        cout << "Locatar adaugat cu succes!\n";
    }
    catch (ServiceException& e) {
        cout << e.get_msg();
    }
}

void Console::delete_locatar_ui() const {
    try {
        int numar_apartament;
        while (true) {
            cout << "Introduceti numarul apartamentului locatarului:\n>>>";
            cin >> numar_apartament;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }

        Locatar &l = srv.find_locatar(numar_apartament);
        cout << "Se va sterge " << l << "\n";
        bool confirmed = YesNoMenu();
        if (confirmed) {
            srv.delete_locatar(numar_apartament);
            cout << "Apartament sters cu succes!\n";
        }
        else {
            cout << "Se anuleaza stergerea\n";
        }
    }
    catch (ServiceException& e) {
        cout << e.get_msg();
    }
}

void Console::modify_locatar_ui() const {
    try {
        int numar_apartament;
        while (true) {
            cout << "Introduceti numarul apartamentului pe care doriti sa il modificati:\n>>>";
            cin >> numar_apartament;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }

        string nume_nou;
        cout << "Introduceti numele locatarului:\n>>>";
        cin >> nume_nou;

        double suprafata_noua;
        while (true) {
            cout << "Introduceti suprafata apartamentului locatarului:\n>>>";
            cin >> suprafata_noua;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }

        string tip_nou;
        cout << "Introduceti tipul apartamentului locatarului:\n>>>";
        cin >> tip_nou;

        Locatar &l = srv.find_locatar(numar_apartament);
        cout << "Se va modifica " << l << "\n";
        bool confirmed = YesNoMenu();
        if (confirmed) {
            srv.modify_locatar(numar_apartament, nume_nou, suprafata_noua, tip_nou);
            cout << "Apartament modificat cu succes!\n";
        }
        else {
            cout << "Se anuleaza modificarea.\n";
        }
    }
    catch (ServiceException& e) {
        cout << e.get_msg();
    }
}

void Console::find_locatar_ui() const {
    try {
        int numar_apartament;
        while (true) {
            cout << "Introduceti numarul apartamentului pe care doriti sa il cautati:\n>>>";
            cin >> numar_apartament;
            if (!cin.fail()) break;
            cout << "Input invalid\n";
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
        Locatar& l = srv.find_locatar(numar_apartament);
        cout << l << "\n";
    }
    catch (ServiceException& e) {
        cout << e.get_msg();
    }
}

void Console::filter_after_type_ui(const vector<Locatar>& list) {
    string type;
    cout << "Introduceti tipul dupa care sa se realizeze filtrarea:\n>>>";
    cin >> type;
    vector<Locatar>filtered_list = ServiceLocatari::filter_after_type(list, type);
    print_all_locatari(filtered_list);
}

void Console::filter_after_surface_ui(const vector<Locatar>& list) {
    double suprafata_minima;
    while (true) {
        cout << "Introduceti suprafata minima dupa care sa se realizeze filtrarea:\n>>>";
        cin >> suprafata_minima;
        if (!cin.fail()) break;
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
    }
    vector<Locatar>filtered_list = ServiceLocatari::filter_after_surface(list, suprafata_minima);
    print_all_locatari(filtered_list);
}

void Console::sort_after_name_ui(const vector<Locatar>& list) {
    vector<Locatar>sorted_list = ServiceLocatari::sort_after_name(list);
    print_all_locatari(sorted_list);
}

void Console::sort_after_surface_ui(const vector<Locatar>& list) {
    vector<Locatar>sorted_list = ServiceLocatari::sort_after_surface(list);
    print_all_locatari(sorted_list);
}

void Console::sort_after_type_and_surface_ui(const vector<Locatar>& list) {
    vector<Locatar>sorted_list = ServiceLocatari::sort_after_type_and_surface(list);
    print_all_locatari(sorted_list);
}

void Console::run() const {
    while (true) {
        print_menu();
        int option;
        cout << ">>>";
        cin >> option;
        switch (option) {
            case 1:
                print_all_locatari(srv.get_all_locatari());
                break;

            case 2:
                add_locatar_ui();
                break;

            case 3:
                delete_locatar_ui();
                break;

            case 4:
                modify_locatar_ui();
                break;

            case 5:
                find_locatar_ui();
                break;

            case 6:
                filter_after_type_ui(srv.get_all_locatari());
                break;

            case 7:
                filter_after_surface_ui(srv.get_all_locatari());
                break;

            case 8:
                sort_after_name_ui(srv.get_all_locatari());
                break;

            case 9:
                sort_after_surface_ui(srv.get_all_locatari());
                break;

            case 10:
                sort_after_type_and_surface_ui(srv.get_all_locatari());
                break;

            case 11:
                return;

            default:
                cout << "Optiune invalida!";
        }
    }
}