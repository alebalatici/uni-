//
// Created by Alexandra on 5/18/2026.
//

#include "gui.h"

void GraphicalInterface::initialize_components()
{
    QHBoxLayout* layout_main = new QHBoxLayout;
    setLayout(layout_main);

    QGroupBox* left = new QGroupBox;
    QVBoxLayout* layout_left = new QVBoxLayout;
    left->setLayout(layout_left);

    QGroupBox* right = new QGroupBox;
    QVBoxLayout* layout_right = new QVBoxLayout;
    right->setLayout(layout_right);

    initialize_table(layout_left);
    initialize_radio_buttons(layout_right);
    initialize_elems(layout_left);
    initialize_list(layout_left);
    button_generate_match = new QPushButton("Generate match", this);
    layout_right->addWidget(button_generate_match);

    layout_main->addWidget(left);
    layout_main->addWidget(right);
}

void GraphicalInterface::connect_signal_slots()
{
    QObject::connect(button_add_to_list, &QPushButton::clicked, [this]()
    {
        string nume = edit_nume->text().toStdString();
        string tara = edit_tara->text().toStdString();
        try
        {
            int value = slider_jucatori->value();
            srv.add_jucator(nume, tara, value, 0);
            reload_data(srv.get_all_jucatori());
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(this, "Error", e.what());
        }
    });

    QObject::connect(button_generate_match, &QPushButton::clicked, [this]()
    {
        if (srv.get_all_jucatori().size() < 2)
        {
            QMessageBox::critical(this, "Error", "Not enough players");
            return;
        }

        int index_random1 = std::rand() % srv.get_all_jucatori().size();

        Jucator jucator1 = srv.get_all_jucatori()[index_random1];

        int index_random2 = std::rand() % srv.get_all_jucatori().size();
        while (index_random2 == index_random1)
        {
            index_random2 = std::rand() % srv.get_all_jucatori().size();
        }
        Jucator jucator2 = srv.get_all_jucatori()[index_random2];

        string text = "[" + std::to_string(jucator1.get_rank()) + "]" + jucator1.get_nume() + " vs " +
            "[" + std::to_string(jucator2.get_rank()) + "]" + jucator2.get_nume();
        QMessageBox::information(this, "Info", QString::fromStdString(text));
    });
}

void GraphicalInterface::reload_data(const vector<Jucator>& jucatori)
{
    table_jucatori->clearContents();
    table_jucatori->setRowCount((int)jucatori.size());
    int row = 0;
    for (auto& j : jucatori)
    {
        table_jucatori->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(j.get_nume())));
        table_jucatori->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(j.get_tara())));
        table_jucatori->setItem(row, 2, new QTableWidgetItem(QString::number(j.get_numar_puncte())));
        table_jucatori->setItem(row, 3, new QTableWidgetItem(QString::number(j.get_rank())));
        row++;
    }
}

void GraphicalInterface::initialize_radio_buttons(QVBoxLayout* layout)
{
    QGroupBox* radio = new QGroupBox;
    QVBoxLayout* layout_radio_buttons = new QVBoxLayout;
    radio->setLayout(layout_radio_buttons);

    vector<string> contries = ServiceJucatori::get_all_countries(srv.get_all_jucatori());
    for (auto& contry : contries)
    {
        QRadioButton* radio_button = new QRadioButton(QString::fromStdString(contry));
        layout_radio_buttons->addWidget(radio_button);
        QObject::connect(radio_button, &QRadioButton::clicked, [this, contry]()
        {
             reload_data(ServiceJucatori::filter_by_country(srv.get_all_jucatori(), contry));
        });
    }

    layout->addWidget(radio);
}

void GraphicalInterface::initialize_table(QVBoxLayout* layout)
{
    QGroupBox* table = new QGroupBox;
    QVBoxLayout* layout_table = new QVBoxLayout;
    table->setLayout(layout_table);

    table_jucatori = new QTableWidget(10, 4);
    QStringList header_table;
    header_table << "Nume" << "Tara" << "Numar Puncte" << "Ranking";
    table_jucatori->setHorizontalHeaderLabels(header_table);
    table_jucatori->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout_table->addWidget(table_jucatori);
    layout->addWidget(table);
}

void GraphicalInterface::initialize_list(QVBoxLayout* layout)
{
    QGroupBox* list = new QGroupBox;
    QVBoxLayout* layout_list = new QVBoxLayout;
    list->setLayout(layout_list);

    list_jucatori = new QListWidget;
    list_jucatori->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout_list->addWidget(list_jucatori);
    layout->addWidget(list);
}

void GraphicalInterface::reload_list_data(const vector<Jucator>& jucatori)
{
    list_jucatori->clear();
    for (auto& j : jucatori)
    {
        QString text = QString("%1 | %2 | %3 | %4")
        .arg(QString::fromStdString(j.get_nume()))
        .arg(QString::fromStdString(j.get_tara()))
        .arg(QString::number(j.get_numar_puncte()))
        .arg(QString::number(j.get_rank()));

        QListWidgetItem* item = new QListWidgetItem(text);
        list_jucatori->addItem(item);
    }
}

void GraphicalInterface::initialize_elems(QVBoxLayout* layout)
{
    QGroupBox* elems = new QGroupBox;
    QVBoxLayout* layout_elems = new QVBoxLayout;
    elems->setLayout(layout_elems);

    QFormLayout* layout_form = new QFormLayout;

    edit_nume = new QLineEdit;
    edit_tara = new QLineEdit;

    layout_form->addRow(new QLabel("Numele jucatorului: "), edit_nume);
    layout_form->addRow(new QLabel("Tara jucatorului: "), edit_tara);

    slider_jucatori =  new QSlider(Qt::Horizontal);

    slider_jucatori->setRange(1, 100);

    layout_form->addRow(slider_jucatori);

    button_add_to_list = new QPushButton("Adauga in lista", this);
    layout_form->addRow(button_add_to_list);

    layout_elems->addLayout(layout_form);
    layout->addWidget(elems);
}