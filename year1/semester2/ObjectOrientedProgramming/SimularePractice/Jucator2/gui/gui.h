//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR2_GUI_H
#define JUCATOR2_GUI_H

#include <QWidget>
#include <QtWidgets>
#include "../service/service_jucatori.h"

class GraphicalInterface : public QWidget {
    private:
    ServiceJucatori& srv;

    QTableWidget* table_jucatori{};

    QListWidget* list_jucatori = nullptr;

    QLineEdit* edit_nume = nullptr;
    QLineEdit* edit_tara = nullptr;

    QSlider* slider_jucatori = nullptr;

    QPushButton* button_add_to_list = nullptr;
    QPushButton* button_generate_match = nullptr;

    void initialize_components();
    void connect_signal_slots();
    void initialize_list(QVBoxLayout* layout);
    void reload_list_data(const vector<Jucator>& jucatori);
    void initialize_radio_buttons(QVBoxLayout* layout);
    void initialize_table(QVBoxLayout* layout);
    void initialize_elems(QVBoxLayout* layout);
    void reload_data(const vector<Jucator>& jucatori);
public:
    GraphicalInterface(ServiceJucatori& srv) : srv{srv}
    {
        initialize_components();
        connect_signal_slots();
        reload_data(srv.get_all_jucatori());
    }
};

#endif //JUCATOR2_GUI_H
