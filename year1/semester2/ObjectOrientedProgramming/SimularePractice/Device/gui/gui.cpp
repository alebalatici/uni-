//
// Created by Alexandra on 5/17/2026.
//

#include "gui.h"

void GraphicalInterface::reload_data(const vector<Device>& devices)
{
    lista_devices->clear();
    for (const Device& device : devices)
    {
        QString text = QString("%1 | %2 | %3")
        .arg(QString::fromStdString(device.get_model()))
        .arg(QString::fromStdString(device.get_culoare()))
        .arg(QString::number(device.get_pret()));

        QListWidgetItem* item = new QListWidgetItem(text);
        if (device.get_culoare() == "rosu")
            item->setBackground(Qt::red);
        else if (device.get_culoare() == "albastru")
            item->setBackground(Qt::blue);
        else if (device.get_culoare() == "negru")
        {
            item->setBackground(Qt::black);
            item->setForeground(Qt::white);
        }
        else if (device.get_culoare() == "galben")
            item->setBackground(Qt::yellow);

        lista_devices->addItem(item);
    }
}

void GraphicalInterface::initialize_list(QVBoxLayout* layout)
{
    QGroupBox* list = new QGroupBox;
    QVBoxLayout* layout_list = new QVBoxLayout(list);
    list->setLayout(layout_list);

    lista_devices->setSelectionBehavior(QAbstractItemView::SelectRows);

    layout_list->addWidget(lista_devices);
    layout->addWidget(list);
}

void GraphicalInterface::initialize_components()
{
    QHBoxLayout* layout_main = new QHBoxLayout(this);
    setLayout(layout_main);

    QGroupBox* left = new QGroupBox;
    QVBoxLayout* layout_left = new QVBoxLayout(this);
    left->setLayout(layout_left);

    QGroupBox* right = new QGroupBox;
    QVBoxLayout* layout_right = new QVBoxLayout(this);
    right->setLayout(layout_right);

    initialize_list(layout_left);
    initialize_form_sortare(layout_right);
    layout_left->addWidget(edit_model_an);

    layout_main->addWidget(left);
    layout_main->addWidget(right);
}

void GraphicalInterface::connect_signal_slots()
{
    QObject::connect(button_sortare_model, &QPushButton::clicked, [&]()
    {
        reload_data(ServiceDevice::sort_by_model_ascending(srv.get_all_devices()));
    });
    QObject::connect(button_sortare_an, &QPushButton::clicked, [&]()
    {
        reload_data(ServiceDevice::sort_by_pret_ascending(srv.get_all_devices()));
    });
    QObject::connect(button_nesortare, &QPushButton::clicked, [&]()
    {
        reload_data(srv.get_all_devices());
    });

    QObject::connect(lista_devices, &QListWidget::itemClicked, [&]()
    {
        auto item = lista_devices->currentItem();
        string model = item->text().split('|').at(0).trimmed().toStdString();
        string culoare = item->text().split('|').at(1).trimmed().toStdString();
        double pret = item->text().split('|').at(2).trimmed().toDouble();
        Device& d = srv.find_device(model, culoare, pret);
        string text = "Modelul este: " + d.get_model() + ", Anul este: " + std::to_string(d.get_an());
        edit_model_an->setText(QString::fromStdString(text));
    });
}

void GraphicalInterface::initialize_form_sortare(QVBoxLayout* layout)
{
    QGroupBox* sortare = new QGroupBox("Sortare");
    QVBoxLayout* layout_sortare = new QVBoxLayout(sortare);
    sortare->setLayout(layout_sortare);

    layout_sortare->addWidget(button_sortare_model);
    layout_sortare->addWidget(button_sortare_an);
    layout_sortare->addWidget(button_nesortare);

    layout->addWidget(sortare);
}