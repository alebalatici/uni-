//
// Created by Alexandra on 5/17/2026.
//

#ifndef DEVICE_GUI_H
#define DEVICE_GUI_H

#include <QWidget>
#include <QtWidgets>

#include "../service/service_device.h"

class GraphicalInterface : public QWidget {
    private:
    ServiceDevice& srv;

    QListWidget* lista_devices = new QListWidget;

    QLineEdit* edit_model_an = new QLineEdit;

    QPushButton* button_sortare_model = new QPushButton("Sortare Model");
    QPushButton* button_sortare_an = new QPushButton("Sortare An");
    QPushButton* button_nesortare = new QPushButton("Nesortart");

    void reload_data(const vector<Device>& devices);
    void initialize_components();
    void connect_signal_slots();
    void initialize_list(QVBoxLayout* layout);
    void initialize_form_sortare(QVBoxLayout* layout);
public:

    GraphicalInterface(ServiceDevice& _srv) : srv{_srv}
    {
        initialize_components();
        connect_signal_slots();
        reload_data(srv.get_all_devices());
    }
};



#endif //DEVICE_GUI_H
