//
// Created by Alexandra on 5/18/2026.
//

#include "gui.h"

void GraphicalInterface::connect_signals_slots()
{
    QObject::connect(radio_finala, &QRadioButton::clicked, [&]()
    {
        string nume = edit_nume->text().toStdString();
        int puncte = edit_puncte->text().toInt();
        try
        {
            if (puncte < 0)
            {
                throw std::out_of_range("Puncte must be greater than 0");
            }
            Jucator& j = srv.find_jucator(nume);
            srv.modify_jucator(nume, j.get_tara(), j.get_numar_puncte() + puncte, j.get_ranking());
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, tr("Error"), e.what());
        }
    });

    QObject::connect(radio_semifinala, &QRadioButton::clicked, [&]()
    {
        string nume = edit_nume->text().toStdString();
        int puncte = edit_puncte->text().toInt();
        try
        {
            if (puncte < 0)
            {
                throw std::out_of_range("Puncte must be greater than 0");
            }
            Jucator& j = srv.find_jucator(nume);
            srv.modify_jucator(nume, j.get_tara(), j.get_numar_puncte() + int(70.0/100.0 * puncte), j.get_ranking());
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, tr("Error"), e.what());
        }
    });

    QObject::connect(radio_sferturi, &QRadioButton::clicked, [&]()
    {
        string nume = edit_nume->text().toStdString();
        int puncte = edit_puncte->text().toInt();
        try
        {
            if (puncte < 0)
            {
                throw std::out_of_range("Puncte must be greater than 0");
            }
            Jucator& j = srv.find_jucator(nume);
            srv.modify_jucator(nume, j.get_tara(), j.get_numar_puncte() + int(50.0/100.0 * puncte), j.get_ranking());
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, tr("Error"), e.what());
        }
    });

    QObject::connect(button_recalculeaza_ranking, &QPushButton::clicked, [&]()
    {
        reload_data(srv.recalculeaza_rank(srv.get_all_jucatori()));
    });

    QObject::connect(button_delete_punctaj, &QPushButton::clicked, [&]()
    {
        try
        {
            slider_delete->setRange(0, (int)srv.get_all_jucatori().size());
            int value = slider_delete->value();
            srv.delete_m_jucatori_punctaj(value);
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, tr("Error"), e.what());
        }
    });

    QObject::connect(button_delete_ranking, &QPushButton::clicked, [&]()
    {
        try
        {
            slider_delete->setRange(0, (int)srv.get_all_jucatori().size());
            int value = slider_delete->value();
            srv.delete_m_jucatori_ranking(value);
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::warning(this, tr("Error"), e.what());
        }
    });
}

void GraphicalInterface::initialize_puncte(QVBoxLayout* layout)
{
    QGroupBox* puncte = new QGroupBox;
    QVBoxLayout* puncte_layout = new QVBoxLayout;
    puncte->setLayout(puncte_layout);

    QFormLayout* layout_form = new QFormLayout;
    layout_form->addRow(new QLabel("Nume: "), edit_nume);
    layout_form->addRow(new QLabel("Puncte: "), edit_puncte);

    layout_form->addRow(radio_finala);
    layout_form->addRow(radio_semifinala);
    layout_form->addRow(radio_sferturi);

    puncte_layout->addLayout(layout_form);
    layout->addWidget(puncte);
}

void GraphicalInterface::initialize_delete(QVBoxLayout* layout)
{
    QGroupBox* delete_box = new QGroupBox;
    QVBoxLayout* delete_layout = new QVBoxLayout;
    delete_box->setLayout(delete_layout);

    delete_layout->addWidget(slider_delete);
    delete_layout->addWidget(button_delete_punctaj);
    delete_layout->addWidget(button_delete_ranking);

    layout->addWidget(delete_box);
}

void GraphicalInterface::initialize_components()
{
    QHBoxLayout *main_layout = new QHBoxLayout;
    setLayout(main_layout);

    QGroupBox* left = new QGroupBox;
    QVBoxLayout* left_layout = new QVBoxLayout;
    left->setLayout(left_layout);

    QGroupBox* right = new QGroupBox;
    QVBoxLayout* right_layout = new QVBoxLayout;
    right->setLayout(right_layout);

    initialize_list(left_layout);
    initialize_puncte(right_layout);
    initialize_delete(right_layout);

    left_layout->addWidget(button_recalculeaza_ranking);

    main_layout->addWidget(left);
    main_layout->addWidget(right);
}

void GraphicalInterface::initialize_list(QVBoxLayout* layout)
{
    QGroupBox* list = new QGroupBox;
    QVBoxLayout* list_layout = new QVBoxLayout;
    list->setLayout(list_layout);

    lista_jucatori->setSelectionBehavior(QAbstractItemView::SelectRows);

    list_layout->addWidget(lista_jucatori);
    layout->addWidget(list);
}

void GraphicalInterface::reload_data(const vector<Jucator>& jucatori)
{
    lista_jucatori->clear();
    for (auto &j : jucatori)
    {
        QString text = QString("%1 | %2 | %3 | %4")
        .arg(QString::fromStdString(j.get_nume()))
        .arg(QString::fromStdString(j.get_tara()))
        .arg(QString::number(j.get_numar_puncte()))
        .arg(QString::number(j.get_ranking()));

        QListWidgetItem* item = new QListWidgetItem(text);
        lista_jucatori->addItem(item);
    }
}