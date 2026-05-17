//
// Created by Alexandra on 5/16/2026.
//

#include <QtWidgets>
#ifndef GAMINGSTORE_GUI_H
#define GAMINGSTORE_GUI_H

#include "../service/service_joc.h"

class GraphicalInterface : public QWidget {
    Q_OBJECT
private:
    ServiceJoc& srv;

    void initialize_components();
    void initialize_table(QVBoxLayout* layout);
    void connect_signal_slots();
    void reload_data(const vector<Joc>& jocuri);
    QTableWidget* table_jocuri;
    QLabel* label_age_rating = new QLabel("Select an Item");
    QPushButton* button_sortare_pret = new QPushButton("Sortare Pret");
    QPushButton* button_refresh = new QPushButton("Refresh");
    QPushButton* button_filtrare = new QPushButton("Jocuri recomandate pentru copii");
public:
    GraphicalInterface(ServiceJoc& srv) : srv{srv}
    {
        initialize_components();
        connect_signal_slots();
        reload_data(srv.get_all_jocuri());
    }

    void write_on_label();
    void coloreaza_rand(int row, QColor color);
};



#endif //GAMINGSTORE_GUI_H
