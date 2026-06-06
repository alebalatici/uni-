//
// Created by Alexandra on 5/17/2026.
//

#ifndef DOCTORI_GUI_H
#define DOCTORI_GUI_H

#include <QtWidgets>
#include "../service/service_doctor.h"

class GraphicalInterface : public QWidget {
private:
    ServiceDoctor& srv;

    QListWidget* lista_doctori = new QListWidget;

    QPushButton* button_filtrare_nume = new QPushButton("Filtreaza dupa nume");
    QPushButton* button_filtrare_sectie = new QPushButton("Filtreaza dupa sectie");
    QPushButton* button_filtrare_toate = new QPushButton("Toate");

    QPushButton* button_refresh = new QPushButton("Refresh");

    QLineEdit* edit_filtrare_sectie = new QLineEdit;
    QLineEdit* edit_filtrare_nume = new QLineEdit;
    QLineEdit* edit_detalii_doctor = new QLineEdit;

    /**
     * Realizeaza conexiunile dintre evenimentele componentelor grafice
     */

    void connect_signal_slots();
    /**
     * Actualizeaza lista din interfata cu noua lista de doctori primita
     * @param doctori Lista de doctori primita
     */
    void reload_data(const vector<Doctor>& doctori);

    /**
     * Initializeaza componentele grafice principale ale ferestrei
     */
    void initialize_components();

    /**
     * Configureaza si adauga in layout-ul primit componentele specifice pentru afisarea listei
     * @param layout Layout-ul primit
     */
    void initialize_list(QVBoxLayout* layout);

    /**
     * Configureaza si adauga in layout-ul primit componentele specifice filtrarii
     * @param layout Layout-ul primit
     */
    void initialize_filtrare(QVBoxLayout* layout);
public:
    GraphicalInterface(ServiceDoctor& _srv) : srv{_srv}
    {
        initialize_components();
        connect_signal_slots();
        reload_data(srv.get_all_doctori());
    };
};



#endif //DOCTORI_GUI_H
