//
// Created by Alexandra on 5/17/2026.
//

#include "gui.h"

void GraphicalInterface::connect_signal_slots()
{
    QObject::connect(lista_doctori, &QListWidget::itemClicked, [&]()
    {
        auto item = lista_doctori->currentItem();
        string nume = item->text().split("|").at(0).trimmed().toStdString();
        string prenume = item->text().split("|").at(1).trimmed().toStdString();
        Doctor& doctor = srv.find_by_nume_prenume(nume, prenume);
        edit_detalii_doctor->setText(QString::fromStdString(doctor.get_cnp()));
    });

    QObject::connect(button_refresh, &QPushButton::clicked, [&]()
    {
        reload_data(srv.get_all_doctori());
    });

    QObject::connect(button_filtrare_nume, &QPushButton::clicked, [&]()
    {
        string nume = edit_filtrare_nume->text().toStdString();
        edit_filtrare_nume->clear();
        reload_data(ServiceDoctor::filter_by_nume(srv.get_all_doctori(), nume));
    });

    QObject::connect(button_filtrare_sectie, &QPushButton::clicked, [&]()
    {
        string sectie = edit_filtrare_sectie->text().toStdString();
        edit_filtrare_sectie->clear();
        reload_data(ServiceDoctor::filter_by_sectie(srv.get_all_doctori(), sectie));
    });

    QObject::connect(button_filtrare_toate, &QPushButton::clicked, [&]()
    {
        string nume = edit_filtrare_nume->text().toStdString();
        edit_filtrare_nume->clear();
        string sectie = edit_filtrare_sectie->text().toStdString();
        edit_filtrare_sectie->clear();
        reload_data(ServiceDoctor::filter_by_nume(ServiceDoctor::filter_by_sectie(srv.get_all_doctori(), sectie), nume));
    });
}

void GraphicalInterface::reload_data(const vector<Doctor>& doctori)
{
    lista_doctori->clear();
    for (auto& doctor : doctori)
    {
        QString item_text = QString("%1 | %2 | %3")
        .arg(QString::fromStdString(doctor.get_nume()))
        .arg(QString::fromStdString(doctor.get_prenume()))
        .arg(QString::fromStdString(doctor.get_sectie()));

        QListWidgetItem* item = new QListWidgetItem(item_text);

        if (doctor.get_concediu() == 0)
        {
            item->setBackground(Qt::green);
        }
        else
        {
            item->setBackground(Qt::red);
        }
        lista_doctori->addItem(item);
    }
}

void GraphicalInterface::initialize_list(QVBoxLayout* layout)
{
    QGroupBox* list = new QGroupBox;
    QVBoxLayout* list_layout = new QVBoxLayout;
    list->setLayout(list_layout);

    lista_doctori->setSelectionBehavior(QAbstractItemView::SelectRows);

    list_layout->addWidget(lista_doctori);
    layout->addWidget(list);
}

void GraphicalInterface::initialize_filtrare(QVBoxLayout* layout)
{
    QGroupBox* filtrare = new QGroupBox("Filtrare");
    QVBoxLayout* filtrare_layout = new QVBoxLayout;
    filtrare->setLayout(filtrare_layout);

    QFormLayout* form_layout = new QFormLayout;

    form_layout->addRow(new QLabel("Numele dupa care sa se realizeze filtrarea: "), edit_filtrare_nume);
    form_layout->addRow(new QLabel("Sectia dupa care sa se realizeze filtrarea: "), edit_filtrare_sectie);
    form_layout->addRow(button_filtrare_nume);
    form_layout->addRow(button_filtrare_sectie);
    form_layout->addRow(button_filtrare_toate);

    filtrare_layout->addLayout(form_layout);
    layout->addWidget(filtrare);
}

void GraphicalInterface::initialize_components()
{
    QHBoxLayout* main_layout = new QHBoxLayout;
    setLayout(main_layout);

    QGroupBox* left = new QGroupBox;
    QVBoxLayout* left_layout = new QVBoxLayout;
    left->setLayout(left_layout);

    QGroupBox* right = new QGroupBox;
    QVBoxLayout* right_layout = new QVBoxLayout;
    right->setLayout(right_layout);

    initialize_list(left_layout);
    initialize_filtrare(right_layout);
    edit_detalii_doctor->setReadOnly(true);
    left_layout->addWidget(edit_detalii_doctor);
    right_layout->addWidget(button_refresh);

    main_layout->addWidget(left);
    main_layout->addWidget(right);
}