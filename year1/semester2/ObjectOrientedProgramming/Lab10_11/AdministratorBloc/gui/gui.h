#ifndef ADMINISTRATORBLOC_GUI_H
#define ADMINISTRATORBLOC_GUI_H

#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QGroupBox>
#include <QRadioButton>
#include "../service/service_locatari.h"
#include "notification_list_window.h"

using std::vector;
using std::string;

class GraphicalInterface : public QWidget {
    Q_OBJECT
private:
    ServiceLocatari& srv;

    QVBoxLayout* layout_butoane_dinamice;

    QLabel* label_apartament_adaugare = new QLabel{"Numarul apartamentului:"};
    QLabel* label_nume_adaugare = new QLabel{"Numele locatarului:"};
    QLabel* label_suprafata_adaugare = new QLabel{"Suprafata apartamentului:"};
    QLabel* label_tip_adaugare = new QLabel{"Tipul apartamentului:"};

    QLabel* label_apartament_stergere = new QLabel{"Numarul apartamentului:"};

    QLabel* label_apartament_modificare = new QLabel{"Numarul apartamentului:"};
    QLabel* label_nume_modificare = new QLabel{"Numele locatarului:"};
    QLabel* label_suprafata_modificare = new QLabel{"Suprafata apartamentului:"};
    QLabel* label_tip_modificare = new QLabel{"Tipul apartamentului:"};

    QLabel* label_filter_criteria_tip = new QLabel(tr("Tipul dupa care se filtreaza:"));
    QLabel* label_filter_criteria_suprafata = new QLabel(tr("Suprafata minima dupa care se filtreaza:"));

    QLabel* label_apartament_cautare = new QLabel{"Numarul apartamentului:"};

    QLabel* label_undo = new QLabel(tr("Undo"));


    QLineEdit* edit_apartament_adaugare;
    QLineEdit* edit_nume_adaugare;
    QLineEdit* edit_suprafata_adaugare;
    QLineEdit* edit_tip_adaugare;

    QLineEdit* edit_apartament_stergere;

    QLineEdit* edit_apartament_modificare;
    QLineEdit* edit_nume_modificare;
    QLineEdit* edit_suprafata_modificare;
    QLineEdit* edit_tip_modificare;

    QLineEdit* edit_filtrare_tip;
    QLineEdit* edit_filtrare_suprafata;

    QLineEdit* edit_apartament_cautare;

    QPushButton* button_add_locatar;
    QPushButton* button_delete_locatar;
    QPushButton* button_sort_locatari;
    QPushButton* button_filter_locatari_tip;
    QPushButton* button_filter_locatari_suprafata;
    QPushButton* button_reload_data;
    QPushButton* button_modify_locatari;
    QPushButton* button_undo;
    QPushButton* button_find_locatar;
    QPushButton* button_notification_list;


    QGroupBox* group_box_sortare = new QGroupBox(tr("Sortare"));
    QGroupBox* group_box_filtrare = new QGroupBox(tr("Filtrare"));
    QGroupBox* group_box_adaugare = new QGroupBox(tr("Adaugare"));
    QGroupBox* group_box_stergere = new QGroupBox(tr("Stergere"));
    QGroupBox* group_box_modificare = new QGroupBox(tr("Modificare"));
    QGroupBox* group_box_cautare = new QGroupBox(tr("Cautare"));
    QGroupBox* group_box_lista_notificari = new QGroupBox(tr("Lista de Notificari"));
    QGroupBox* group_box_dictionar = new QGroupBox(tr("Contor Tip Locatari"));

    QRadioButton* radio_sortare_nume = new QRadioButton(QString::fromStdString(std::string("Sortare dupa nume")));
    QRadioButton* radio_sortare_suprafata = new QRadioButton(QString::fromStdString(std::string("Sortare dupa suprafata")));
    QRadioButton* radio_sortare_tip_suprafata = new QRadioButton(QString::fromStdString(std::string("Sortare dupa tip si suprafata")));

    QTableWidget* table_locatari;

    NotificationListWindow* dialog = new NotificationListWindow(srv, this);

    void initialize_gui_components();
    void initialize_form_adaugare(QVBoxLayout* layout);
    void initialize_form_stergere(QVBoxLayout* layout);
    void initialize_form_sortare(QVBoxLayout* layout);
    void initialize_form_filtrare(QVBoxLayout* layout);
    void initialize_form_modificare(QVBoxLayout* layout);
    void initialize_form_undo(QVBoxLayout* layout);
    void initialize_form_reload(QVBoxLayout* layout);
    void initialize_form_cautare(QVBoxLayout* layout);
    void inittialize_form_contor_tip(QVBoxLayout* layout);
    void initialize_form_lista_notificari(QVBoxLayout* layout);
    void initialize_table(QVBoxLayout* layout);
    void connect_signals_slots();
    void reload_data(vector<Locatar> locatari);
    void open_new_window();
    void set_barbie_style();

    void set_buttons_visibility();
   // void show_button(QGroupBox* group_box ,QButton* button)
public:
    GraphicalInterface(ServiceLocatari& _srv) : srv { _srv }
    {
        srv.initialize_dictionar();
        initialize_gui_components();
        connect_signals_slots();
        reload_data(srv.get_all_locatari());
    }

    void add_locatari_gui();
    void delete_locatari_gui();
    void sort_locatari_gui();
    void filter_locatari_tip_gui();
    void filter_locatari_suprafata_gui();
    void modify_locatari_gui();
    void find_locatari_gui();
    void undo_gui();
};

#endif //ADMINISTRATORBLOC_GUI_H
