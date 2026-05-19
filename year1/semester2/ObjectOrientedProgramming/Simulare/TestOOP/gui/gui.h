//
// Created by Alexandra on 5/19/2026.
//

#ifndef TESTOOP_GUI_H
#define TESTOOP_GUI_H

#include <QWidget>
#include <QtWidgets>

#include "../service/service_radiation.h"

class GraphicalInterface : public QWidget {
    private:
    ServiceRadiation& srv;

    QListWidget* lista_radiatii = nullptr;

    QLineEdit* edit_id = nullptr;
    QLineEdit* edit_description = nullptr;
    QLineEdit* edit_frecventa = nullptr;
    QLineEdit* edit_tip_frecventa = nullptr;
    QLineEdit* edit_filtrare = nullptr;

    QSlider* slider_filtrare = nullptr;

    QPushButton* button_adaugare = nullptr;


    /**
     * Initializeaza formularul de filtrare
     * @param layout Layout-ul in care se pune
     */
    void initialize_form_filtrare(QVBoxLayout* layout)
    {
        QVBoxLayout* layout_filtrare = new QVBoxLayout;
        QGroupBox* filtrare = new QGroupBox("Filtrare");
        filtrare->setLayout(layout_filtrare);

        slider_filtrare = new QSlider(Qt::Horizontal);
        slider_filtrare->setRange(0, 100);
        edit_filtrare = new QLineEdit;

        layout_filtrare->addWidget(slider_filtrare);
        layout_filtrare->addWidget(edit_filtrare);

        layout->addWidget(filtrare);
    }

    /**
     * Initializeaza formularul de adaugare
     * @param layout Layout-ul in care se pun
     */
    void initialize_form_adaugare(QVBoxLayout* layout)
    {
        QVBoxLayout* layout_adaugare = new QVBoxLayout;
        QGroupBox* adaugare = new QGroupBox("Adaugare");
        adaugare->setLayout(layout_adaugare);

        QFormLayout* form_adaugare = new QFormLayout;

        edit_id = new QLineEdit;
        edit_description = new QLineEdit;
        edit_frecventa = new QLineEdit;
        edit_tip_frecventa = new QLineEdit;

        form_adaugare->addRow(new QLabel("Id: "), edit_id);
        form_adaugare->addRow(new QLabel("Description: "), edit_description);
        form_adaugare->addRow(new QLabel("Frecventa: "), edit_frecventa);
        form_adaugare->addRow(new QLabel("Tip frecventa: "), edit_tip_frecventa);

        button_adaugare = new QPushButton("Adaugare");
        form_adaugare->addRow(button_adaugare);

        layout_adaugare->addLayout(form_adaugare);
        layout->addWidget(adaugare);
    }

    /**
     * initializeaza lista
     * @param layout Layout-ul in care se pune
     */
    void initialize_list(QVBoxLayout* layout)
    {
        QVBoxLayout* layout_list = new QVBoxLayout;
        QGroupBox* list = new QGroupBox("Lista de radiatii");
        list->setLayout(layout_list);

        lista_radiatii = new QListWidget;
        lista_radiatii->setSelectionBehavior(QAbstractItemView::SelectRows);

        layout_list->addWidget(lista_radiatii);
        layout->addWidget(list);
    }

    /**
     * Initializeaza componentele
     */
    void initialize_components()
    {
        QHBoxLayout* layout_main = new QHBoxLayout;
        setLayout(layout_main);

        QVBoxLayout* layout_left = new QVBoxLayout;
        QGroupBox* left = new QGroupBox;
        left->setLayout(layout_left);

        QVBoxLayout* layout_right = new QVBoxLayout;
        QGroupBox* right = new QGroupBox;
        right->setLayout(layout_right);

        initialize_list(layout_left);
        initialize_form_adaugare(layout_right);
        initialize_form_filtrare(layout_right);

        layout_main->addWidget(left);
        layout_main->addWidget(right);
    }

    /**
     * Conecteaza actiunile de obiecte
     */
    void connect_signals_slots()
    {
        QObject::connect(button_adaugare, &QPushButton::clicked, this, &GraphicalInterface::adaugare_gui);
        QObject::connect(slider_filtrare, &QSlider::valueChanged, [this]()
        {
            int value = slider_filtrare->value();
            string text = edit_filtrare->text().toStdString();
            //reload_data(ServiceRadiation::filtrare_frecventa(srv.get_all_radiatii(), value));
            if (text.empty())
                reload_data(ServiceRadiation::filtrare_frecventa(srv.get_all_radiatii(), value));
            else
                reload_data(ServiceRadiation::filtrare_frecventa(ServiceRadiation::filtrare_string(srv.get_all_radiatii(), text), value));
        });

        QObject::connect(edit_filtrare, &QLineEdit::textChanged, [this]()
        {
            int value = slider_filtrare->value();
            string text = edit_filtrare->text().toStdString();
            if (value == 0)
                reload_data(ServiceRadiation::filtrare_string(srv.get_all_radiatii(), text));
            else
                reload_data(ServiceRadiation::filtrare_frecventa(ServiceRadiation::filtrare_string(srv.get_all_radiatii(), text), value));
        });
    }


    /**
     * Reincarca lista
     * @param radiatii Lista de radiatii
     */
    void reload_data(const vector<Radiation>& radiatii)
    {
        lista_radiatii->clear();
        for (auto& r: radiatii)
        {
            QString text = QString("%1 - %2 : %3 - %4")
            .arg(QString::number(r.get_id()))
            .arg(QString::fromStdString(r.get_description()))
            .arg(QString::number(r.get_frecventa()))
            .arg(QString::fromStdString(r.get_tip_frecventa()));

            QListWidgetItem* item = new QListWidgetItem(text);

            if (r.get_tip_frecventa() == "alpha")
                item->setBackground(Qt::gray);
            else if (r.get_tip_frecventa() == "beta")
                item->setBackground(Qt::green);
            else if (r.get_tip_frecventa() == "gamma")
                item->setBackground(Qt::yellow);
            else if (r.get_tip_frecventa() == "delta")
                item->setBackground(Qt::cyan);
            else if (r.get_tip_frecventa() == "theta")
                item->setBackground(Qt::red);
            lista_radiatii->addItem(item);
        }
    }

    public:
    GraphicalInterface(ServiceRadiation& _srv ) : srv(_srv) {
        initialize_components();
        connect_signals_slots();
        reload_data(srv.get_all_radiatii());
    }

    /**
     * Adaugarea in lista
     */
    void adaugare_gui()
    {
        int id = edit_id->text().toInt();
        string description = edit_description->text().toStdString();
        double frecventa = edit_frecventa->text().toDouble();
        string tip_frecventa = edit_tip_frecventa->text().toStdString();

        edit_id->clear();
        edit_description->clear();
        edit_frecventa->clear();
        edit_tip_frecventa->clear();

        try
        {
            srv.add_radiation(id, description, frecventa, tip_frecventa);
            reload_data(srv.get_all_radiatii());
            QMessageBox::information(this, "Info", "Adaugare efectuata cu succes");
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, "Error", QString::fromStdString(e.what()));
        }
    }
};

#endif //TESTOOP_GUI_H
