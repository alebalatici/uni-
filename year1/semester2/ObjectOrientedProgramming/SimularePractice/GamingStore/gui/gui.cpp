//
// Created by Alexandra on 5/16/2026.
//

#include "gui.h"

void GraphicalInterface::initialize_components()
{
    QHBoxLayout* layout_main = new QHBoxLayout;
    setLayout(layout_main);

    QGroupBox* left = new QGroupBox("Left");
    QVBoxLayout* layout_left = new QVBoxLayout;
    left->setLayout(layout_left);

    QGroupBox* right = new QGroupBox("Right");
    QVBoxLayout* layout_right = new QVBoxLayout;
    right->setLayout(layout_right);

    initialize_table(layout_left);

    layout_left->addWidget(label_age_rating);
    layout_right->addWidget(button_sortare_pret);
    layout_right->addWidget(button_filtrare);
    layout_right->addWidget(button_refresh);

    layout_main->addWidget(left);
    layout_main->addWidget(right);
}

void GraphicalInterface::initialize_table(QVBoxLayout* layout)
{
    QGroupBox* table = new QGroupBox("Table");
    QVBoxLayout* layout_table = new QVBoxLayout;
    table->setLayout(layout_table);

    table_jocuri = new QTableWidget(10, 2);
    QStringList header_table;
    header_table << "Titlu" << "Pret";

    table_jocuri->setHorizontalHeaderLabels(header_table);
    table_jocuri->setFocusPolicy(Qt::StrongFocus);
    table_jocuri->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    layout_table->addWidget(table_jocuri);
    layout->addWidget(table);
}

void GraphicalInterface::connect_signal_slots()
{
    QObject::connect(table_jocuri, &QTableWidget::itemClicked, this, &GraphicalInterface::write_on_label);
    QObject::connect(button_sortare_pret, &QPushButton::clicked, [&]()
    {
        reload_data(ServiceJoc::sort_by_price_ascending(srv.get_all_jocuri()));
    });
    QObject::connect(button_filtrare, &QPushButton::clicked, [&]()
    {
        reload_data(ServiceJoc::filter_by_age_rating(srv.get_all_jocuri(), 12));
    });
    QObject::connect(button_refresh, &QPushButton::clicked, [&]()
    {
        reload_data(srv.get_all_jocuri());
    });
}

void GraphicalInterface::coloreaza_rand(int row, QColor color)
{
    for (int col = 0; col < table_jocuri->columnCount(); ++col)
    {
        if (auto* item = table_jocuri->item(row, col))
        {
            item->setBackground(color);
            if (color == Qt::black)
            {
                item->setForeground(Qt::white);
            }
        }
    }
}

void GraphicalInterface::reload_data(const vector<Joc>& jocuri)
{
    table_jocuri->clear();
    table_jocuri->setRowCount(int(jocuri.size()));
    int item_no = 0;
    for (auto &j : jocuri)
    {
        table_jocuri->setItem(item_no, 0, new QTableWidgetItem(QString::fromStdString(j.get_titlu())));
        table_jocuri->setItem(item_no, 1, new QTableWidgetItem(QString::number(j.get_pret())));
        if (j.get_platforma() == "PC")
            coloreaza_rand(item_no, Qt::black);
        else if (j.get_platforma() == "PlayStation")
            coloreaza_rand(item_no, Qt::blue);
        else if (j.get_platforma() == "XBOX")
            coloreaza_rand(item_no, Qt::green);
        else if (j.get_platforma() == "Nintendo")
            coloreaza_rand(item_no, Qt::red);
        item_no++;
    }
}

void GraphicalInterface::write_on_label()
{
    int row = table_jocuri->currentRow();
    if (row < 0) return;
    auto item = table_jocuri->item(row, 0);
    if (!item) return;
    string titlu = item->text().toStdString();
    try
    {
        Joc& joc = srv.find_joc(titlu);
        string text = "Age-Rating-ul este " + std::to_string(joc.get_age_rating());
        label_age_rating->setText(QString::fromStdString(text));
    }
    catch (std::exception& e)
    {
        QMessageBox::warning(this, "Warning", e.what());
    }
}