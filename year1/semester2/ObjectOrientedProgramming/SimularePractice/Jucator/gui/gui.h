//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR_GUI_H
#define JUCATOR_GUI_H

#include <QWidget>
#include <QtWidgets>
#include "../service/service_jucatori.h"

class GraphicalInterface : public QWidget {
    private:
    ServiceJucatori& srv;

    QListWidget* lista_jucatori = new QListWidget;
    QLineEdit* edit_nume = new QLineEdit;
    QLineEdit* edit_puncte = new QLineEdit;

    QRadioButton* radio_finala = new QRadioButton("Finala");
    QRadioButton* radio_semifinala = new QRadioButton("Semifinala");
    QRadioButton* radio_sferturi = new QRadioButton("Sferturi de finala");

    QPushButton* button_recalculeaza_ranking = new QPushButton("Recalculeaza ranking");
    QPushButton* button_delete_punctaj = new QPushButton("Elimina jucatori (punctaj)");
    QPushButton* button_delete_ranking = new QPushButton("Elimina jucatori (ranking)");

    QSlider* slider_delete = new QSlider(Qt::Horizontal);
    void connect_signals_slots();
    void initialize_components();
    void initialize_list(QVBoxLayout* layout);
    void reload_data(const vector<Jucator>& jucatori);
    void initialize_puncte(QVBoxLayout* layout);
    void initialize_delete(QVBoxLayout* layout);
    public:
    GraphicalInterface(ServiceJucatori& _srv) : srv{_srv}
    {
        initialize_components();
        connect_signals_slots();
        reload_data(srv.get_all_jucatori());
    }
};



#endif //JUCATOR_GUI_H
