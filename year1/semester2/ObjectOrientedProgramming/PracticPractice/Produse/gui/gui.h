//
// Created by Alexandra on 5/19/2026.
//

#ifndef PRODUSE_GUI_H
#define PRODUSE_GUI_H

#include <QWidget>
#include <QtWidgets>

#include "../service/service_produs.h"
#include "my_table.h"
#include "my_list.h"

class GraphicalInterface: public QWidget {
    Q_OBJECT
    private:
    ServiceProdus& srv;

    QTableView* table_produse = nullptr;
    MyTable* model_table = nullptr;

    //optional
    QListView* list_produse = nullptr;
    MyList* model_list = nullptr;

    QSlider *slider_pret = nullptr;
    QLabel* label_slider = nullptr;

    QLineEdit* edit_id = nullptr;
    QLineEdit* edit_nume = nullptr;
    QLineEdit* edit_tip = nullptr;
    QLineEdit* edit_pret = nullptr;

    QPushButton* button_adaugare = nullptr;

    void initialize_table(QVBoxLayout* layout)
    {
        QGroupBox* table = new QGroupBox;
        QVBoxLayout* table_layout = new QVBoxLayout;
        table->setLayout(table_layout);

        table_produse->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_produse->setSelectionMode(QAbstractItemView::SingleSelection);

        table_layout->addWidget(table_produse);
        layout->addWidget(table);
    }

    void initialize_list(QVBoxLayout* layout)
    {
        QGroupBox* list = new QGroupBox;
        QVBoxLayout* list_layout = new QVBoxLayout;
        list->setLayout(list_layout);

        list_produse->setSelectionBehavior(QAbstractItemView::SelectRows);

        list_layout->addWidget(list_produse);
        layout->addWidget(list);
    }

    void initialize_form_adaugare(QVBoxLayout* layout)
    {
        QGroupBox* adaugare = new QGroupBox;
        QVBoxLayout* adaugare_layout = new QVBoxLayout;
        adaugare->setLayout(adaugare_layout);

        QFormLayout* form_layout = new QFormLayout;

        edit_id = new QLineEdit;
        edit_nume = new QLineEdit;
        edit_tip = new QLineEdit;
        edit_pret = new QLineEdit;

        form_layout->addRow(new QLabel("Id:"), edit_id);
        form_layout->addRow(new QLabel("Nume:"), edit_nume);
        form_layout->addRow(new QLabel("Tip:"), edit_tip);
        form_layout->addRow(new QLabel("Pret:"), edit_pret);

        button_adaugare = new QPushButton("Adaugare");
        form_layout->addRow(button_adaugare);

        adaugare_layout->addLayout(form_layout);
        layout->addWidget(adaugare);
    }

    void initialize_components()
    {
        QHBoxLayout* main_layout = new QHBoxLayout;
        setLayout(main_layout);

        QGroupBox* left = new QGroupBox;
        QVBoxLayout* left_layout = new QVBoxLayout;
        left->setLayout(left_layout);

        QGroupBox* right = new QGroupBox;
        QVBoxLayout* right_layout = new QVBoxLayout;
        right->setLayout(right_layout);

        initialize_table(left_layout);
        initialize_list(right_layout);

        slider_pret = new QSlider(Qt::Horizontal);
        slider_pret->setRange(0, 5000);
        left_layout->addWidget(slider_pret);

        label_slider = new QLabel;
        left_layout->addWidget(label_slider);

        initialize_form_adaugare(left_layout);

        main_layout->addWidget(left);
        main_layout->addWidget(right);
    }

    void connect_signals_slots()
    {
        QObject::connect(slider_pret, &QSlider::valueChanged, this, [this]()
        {
            double value = slider_pret->value();
            label_slider->setText("Slider Value: " + QString::number(value));
            model_table->setPret(value);
            model_list->setPret(value);
        });

        QObject::connect(button_adaugare, &QPushButton::clicked, this, [this]()
        {
            try
            {
                int id = edit_id->text().toInt();
                string nume = edit_nume->text().toStdString();
                string tip = edit_tip->text().toStdString();
                double pret = edit_pret->text().toDouble();

                edit_id->clear();
                edit_nume->clear();
                edit_tip->clear();
                edit_pret->clear();

                srv.add_produs(id, nume, tip, pret);
                reload_data(srv.get_all_produse());
                QMessageBox::information(this, "Info", "Added produs successfully");
            }
            catch (exception& e)
            {
                QMessageBox::warning(this, "Warning", e.what());
            }
        });
    }
    
    void reload_data(const vector<Produs>& produse)
    {
        model_table->setProduse(ServiceProdus::sort_by_price(produse));
        model_list->setProduse(ServiceProdus::sort_by_price(produse));
    }

    public:
    GraphicalInterface(ServiceProdus& _srv) : srv(_srv)
    {
        table_produse = new QTableView;
        model_table = new MyTable(srv.get_all_produse());
        table_produse->setModel(model_table);

        list_produse = new QListView;
        model_list = new MyList(srv.get_all_produse());\
        list_produse->setModel(model_list);

        initialize_components();
        connect_signals_slots();
        reload_data(srv.get_all_produse());
    }
};

#endif //PRODUSE_GUI_H
