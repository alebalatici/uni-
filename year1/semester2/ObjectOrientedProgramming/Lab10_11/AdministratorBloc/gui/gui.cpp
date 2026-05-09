#include "gui.h"

void GraphicalInterface::initialize_form_adaugare(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_adaugare->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;

    edit_apartament_adaugare = new QLineEdit;
    edit_nume_adaugare = new QLineEdit;
    edit_suprafata_adaugare = new QLineEdit;
    edit_tip_adaugare = new QLineEdit;

    layout_form->addRow(label_apartament_adaugare, edit_apartament_adaugare);
    layout_form->addRow(label_nume_adaugare, edit_nume_adaugare);
    layout_form->addRow(label_suprafata_adaugare, edit_suprafata_adaugare);
    layout_form->addRow(label_tip_adaugare, edit_tip_adaugare);

    button_add_locatar = new QPushButton("Adauga apartament");
    layout_form->addRow(button_add_locatar);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_adaugare);
}

void GraphicalInterface::initialize_form_modificare(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_modificare->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;

    edit_apartament_modificare = new QLineEdit;
    edit_nume_modificare = new QLineEdit;
    edit_suprafata_modificare = new QLineEdit;
    edit_tip_modificare = new QLineEdit;

    layout_form->addRow(label_apartament_modificare, edit_apartament_modificare);
    layout_form->addRow(label_nume_modificare, edit_nume_modificare);
    layout_form->addRow(label_suprafata_modificare, edit_suprafata_modificare);
    layout_form->addRow(label_tip_modificare, edit_tip_modificare);

    button_modify_locatari = new QPushButton("Modificare locatari");
    layout_form->addRow(button_modify_locatari);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_modificare);
}

void GraphicalInterface::initialize_form_stergere(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_stergere->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    edit_apartament_stergere = new QLineEdit;

    layout_form->addRow(label_apartament_stergere, edit_apartament_stergere);
    button_delete_locatar = new QPushButton("Sterge locatar");

    layout_form->addRow(button_delete_locatar);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_stergere);
}

void GraphicalInterface::initialize_form_cautare(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_cautare->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    edit_apartament_cautare = new QLineEdit;

    layout_form->addRow(label_apartament_cautare, edit_apartament_cautare);
    button_find_locatar = new QPushButton("Cauta locatar");

    layout_form->addRow(button_find_locatar);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_cautare);
}

void GraphicalInterface::initialize_form_lista_notificari(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_lista_notificari->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;

    button_notification_list = new QPushButton("Deschide lista de notificari");

    layout_form->addRow(button_notification_list);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_lista_notificari);
}

void GraphicalInterface::initialize_form_sortare(QVBoxLayout* layout)
{
    QVBoxLayout* layout_radio_box = new QVBoxLayout;
    this->group_box_sortare->setLayout(layout_radio_box);
    layout_radio_box->addWidget(radio_sortare_nume);
    layout_radio_box->addWidget(radio_sortare_suprafata);
    layout_radio_box->addWidget(radio_sortare_tip_suprafata);

    button_sort_locatari = new QPushButton("Sorteaza locatari");
    layout_radio_box->addWidget(button_sort_locatari);

    layout->addWidget(group_box_sortare);
}

void GraphicalInterface::initialize_form_filtrare(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_filtrare->setLayout(layout_box);

    QFormLayout* layout_form = new QFormLayout;
    edit_filtrare_tip = new QLineEdit;
    layout_form->addRow(label_filter_criteria_tip, edit_filtrare_tip);

    edit_filtrare_suprafata = new QLineEdit;
    layout_form->addRow(label_filter_criteria_suprafata, edit_filtrare_suprafata);

    layout_box->addLayout(layout_form);
    button_filter_locatari_tip = new QPushButton("Filtreaza locatari dupa tip");
    button_filter_locatari_suprafata = new QPushButton("Filtreaza locatari dupa suprafata");
    layout_box->addWidget(button_filter_locatari_tip);
    layout_box->addWidget(button_filter_locatari_suprafata);
    layout->addWidget(group_box_filtrare);
}

//void GraphicalInterface::show_button(QGroupBox* group_box ,QButton* button)
//{

//}

void GraphicalInterface::set_buttons_visibility()
{
    if (srv.get_undo_count() == 0)
        button_undo->setVisible(false);
    else
        button_undo->setVisible(true);

    QLayoutItem* child;
    while ((child = layout_butoane_dinamice->takeAt(0)) != nullptr)
    {
        if (child->widget())
            delete child->widget();
        delete child;
    }

    auto dictionar = srv.get_all_dictionar();
    for (auto const& [tip, count]: dictionar)
    {
        if (count > 0)
        {
            QString text_button = QString::fromStdString("Contor " + tip);
            QPushButton* button = new QPushButton(text_button);

            QObject::connect(button, &QPushButton::clicked, this, [this, tip, count]()
            {
                QString mesaj = "Sunt in total " + QString::number(count) + " locuinte de tip " + QString::fromStdString(tip);
                QMessageBox::information(this, "Info", mesaj);
            });
            layout_butoane_dinamice->addWidget(button);
        }
    }
}

void GraphicalInterface::inittialize_form_contor_tip(QVBoxLayout* layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_dictionar->setLayout(layout_box);

    layout_butoane_dinamice = new QVBoxLayout;
    layout_box->addLayout(layout_butoane_dinamice);

    layout->addWidget(group_box_dictionar);
    set_buttons_visibility();
}

void GraphicalInterface::initialize_table(QVBoxLayout* layout)
{
    int nr_lines = 15;
    int nr_columns = 4;
    this->table_locatari = new QTableWidget{ nr_lines, nr_columns };

    QStringList table_header_list;
    table_header_list << "Apartament" << "Nume" << "Suprafata" << "Tip";
    this->table_locatari->setHorizontalHeaderLabels(table_header_list);
    this->table_locatari->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    layout->addWidget(table_locatari);
}

void GraphicalInterface::initialize_form_undo(QVBoxLayout* layout)
{
    QWidget* form = new QWidget;
    QFormLayout* layout_form = new QFormLayout;
    form->setLayout(layout_form);
    button_undo = new QPushButton("Undo");
    layout_form->addRow(button_undo);
    layout->addWidget(form);
}

void GraphicalInterface::initialize_form_reload(QVBoxLayout* layout)
{
    QWidget* form = new QWidget;
    QFormLayout* layout_form = new QFormLayout;
    form->setLayout(layout_form);
    button_reload_data = new QPushButton("Reload data");
    layout_form->addRow(button_reload_data);
    layout->addWidget(form);
}

void GraphicalInterface::initialize_gui_components()
{
    QHBoxLayout* layout_main = new QHBoxLayout;
    this->setLayout(layout_main);

    QWidget* left = new QWidget;
    QVBoxLayout* layout_left = new QVBoxLayout;
    left->setLayout(layout_left);

    QWidget* right = new QWidget;
    QVBoxLayout* layout_right = new QVBoxLayout;
    right->setLayout(layout_right);

    initialize_form_adaugare(layout_left);
    initialize_form_stergere(layout_left);
    initialize_form_sortare(layout_left);
    initialize_form_filtrare(layout_left);
    initialize_form_modificare(layout_right);
    initialize_form_undo(layout_right);
    initialize_form_reload(layout_right);
    initialize_table(layout_right);
    initialize_form_cautare(layout_right);
    initialize_form_lista_notificari(layout_right);
    inittialize_form_contor_tip(layout_right);

    layout_main->addWidget(left);
    layout_main->addWidget(right);

    set_barbie_style();
}

void GraphicalInterface::connect_signals_slots()
{
    QObject::connect(button_add_locatar, &QPushButton::clicked, this, &GraphicalInterface::add_locatari_gui);
    QObject::connect(button_delete_locatar, &QPushButton::clicked, this, &GraphicalInterface::delete_locatari_gui);
    QObject::connect(button_sort_locatari, &QPushButton::clicked, this, &GraphicalInterface::sort_locatari_gui);
    QObject::connect(button_filter_locatari_tip, &QPushButton::clicked, this, &GraphicalInterface::filter_locatari_tip_gui);
    QObject::connect(button_filter_locatari_suprafata, &QPushButton::clicked, this, &GraphicalInterface::filter_locatari_suprafata_gui);
    QObject::connect(button_modify_locatari, &QPushButton::clicked, this, &GraphicalInterface::modify_locatari_gui);
    QObject::connect(button_undo, &QPushButton::clicked, this, &GraphicalInterface::undo_gui);
    QObject::connect(button_find_locatar, &QPushButton::clicked, this, &GraphicalInterface::find_locatari_gui);
    QObject::connect(button_notification_list, &QPushButton::clicked, this, &GraphicalInterface::open_new_window);
    QObject::connect(button_reload_data, &QPushButton::clicked, [&]()
    {
       this->reload_data(srv.get_all_locatari());
    });
}

void GraphicalInterface::reload_data(vector<Locatar> locatari)
{
    this->table_locatari->clearContents();
    this->table_locatari->setRowCount(int(locatari.size()));

    int line_number = 0;
    for (auto& locatar : locatari)
    {
        this->table_locatari->setItem(line_number, 0, new QTableWidgetItem(QString::number(locatar.get_apartment())));
        this->table_locatari->setItem(line_number, 1, new QTableWidgetItem(QString::fromStdString(locatar.get_nume())));
        this->table_locatari->setItem(line_number, 2, new QTableWidgetItem(QString::number(locatar.get_suprafata())));
        this->table_locatari->setItem(line_number, 3, new QTableWidgetItem(QString::fromStdString(locatar.get_tip())));
        line_number++;
    }
    srv.initialize_dictionar();
    set_buttons_visibility();
}

void GraphicalInterface::add_locatari_gui()
{
    try
    {
        int apartament = edit_apartament_adaugare->text().toInt();
        string nume = edit_nume_adaugare->text().toStdString();
        double suprafata = edit_suprafata_adaugare->text().toDouble();
        string tip = edit_tip_adaugare->text().toStdString();

        edit_apartament_adaugare->clear();
        edit_nume_adaugare->clear();
        edit_suprafata_adaugare->clear();
        edit_tip_adaugare->clear();

        this->srv.add_locatar(apartament, nume, suprafata, tip);
        this->reload_data(this->srv.get_all_locatari());

        QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes."));
    }

    catch(ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void GraphicalInterface::undo_gui()
{
    try
    {
        string undo_type = srv.print_last_undo_operation();
        srv.undo();
        this->reload_data(this->srv.get_all_locatari());
        QMessageBox::information(this, "Info", QString::fromStdString(undo_type) + " efectuat cu succes.");
    }

    catch(ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void GraphicalInterface::modify_locatari_gui()
{
    try
    {
        int apartament = edit_apartament_modificare->text().toInt();
        string nume = edit_nume_modificare->text().toStdString();
        double suprafata = edit_suprafata_modificare->text().toDouble();
        string tip = edit_tip_modificare->text().toStdString();

        edit_apartament_modificare->clear();
        edit_nume_modificare->clear();
        edit_suprafata_modificare->clear();
        edit_tip_modificare->clear();

        this->srv.modify_locatar(apartament, nume, suprafata, tip);
        this->reload_data(this->srv.get_all_locatari());

        QMessageBox::information(this, "Info", QString::fromStdString("Locatar modificat cu succes."));
    }

    catch(ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void GraphicalInterface::delete_locatari_gui()
{
    try
    {
        int apartament = edit_apartament_stergere->text().toInt();
        edit_apartament_stergere->clear();
        this->srv.delete_locatar(apartament);
        this->reload_data(this->srv.get_all_locatari());

        QMessageBox::information(this, "Info", QString::fromStdString("Locatar sters cu succes."));
    }
    catch(ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void GraphicalInterface::find_locatari_gui()
{
    try
    {
        int apartament = edit_apartament_cautare->text().toInt();
        edit_apartament_cautare->clear();
        Locatar l = srv.find_locatar(apartament);

        std::ostringstream oss;
        oss << l;
        QString mesaj = "Locatarul cu numarul apartamentului " + QString::number(apartament) + " este:\n" + QString::fromStdString(oss.str());
        QMessageBox::information(this, "Info", mesaj);
    }
    catch(ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void GraphicalInterface::sort_locatari_gui()
{
    if (this->radio_sortare_nume->isChecked())
        this->reload_data(ServiceLocatari::sort_after_name(srv.get_all_locatari()));
    else if (this->radio_sortare_suprafata->isChecked())
        this->reload_data(ServiceLocatari::sort_after_surface(srv.get_all_locatari()));
    else if (this->radio_sortare_tip_suprafata->isChecked())
        this->reload_data(ServiceLocatari::sort_after_type_and_surface(srv.get_all_locatari()));
}

void GraphicalInterface::filter_locatari_tip_gui()
{
    string filterC = this->edit_filtrare_tip->text().toStdString();
    this->reload_data(ServiceLocatari::filter_after_type(srv.get_all_locatari(), filterC));
}

void GraphicalInterface::filter_locatari_suprafata_gui()
{
    int filterC = this->edit_filtrare_suprafata->text().toInt();
    this->reload_data(ServiceLocatari::filter_after_surface(srv.get_all_locatari(), filterC));
}

void GraphicalInterface::open_new_window()
{
    dialog->setWindowTitle(QString::fromStdString("Lista de Notificari"));
    dialog->resize(500, 450);
    dialog->exec();
}

void GraphicalInterface::set_barbie_style()
{
    this->setStyleSheet(R"(
        QWidget {
            background-color: #FDF1F5; /* Roz foarte deschis și plăcut */
            font-family: 'Segoe UI', Arial, sans-serif;
            font-size: 10pt;
            color: #880E4F; /* Text grena-închis pentru contrast */
        }

        QGroupBox {
            background-color: #FFFFFF;
            border: 2px solid #FF69B4; /* Roz Barbie */
            border-radius: 8px;
            margin-top: 12px;
            font-weight: bold;
            color: #880E4F;
            padding: 8px;
        }

        QGroupBox::title {
            subcontrol-origin: margin;
            subcontrol-position: top-center;
            padding: 0 8px;
            color: #FF1493; /* Roz intens */
        }

        QLineEdit {
            padding: 6px;
            border: 1px solid #FFB6C1;
            border-radius: 6px;
            background-color: #FFF0F5;
            color: #880E4F;
            selection-background-color: #FF69B4;
        }
        QLineEdit:focus {
            border: 1.5px solid #FF1493;
            background-color: #FFFFFF;
        }

        QPushButton {
            background-color: #FF1493; /* Roz Barbie intens */
            color: white;
            border: none;
            border-radius: 6px;
            padding: 7px 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #FF69B4;
        }
        QPushButton:pressed {
            background-color: #C71585;
        }

        QTableWidget {
            background-color: #FFFFFF;
            border: 1px solid #FFB6C1;
            border-radius: 6px;
            gridline-color: #F8BBD0;
        }
        QTableWidget::item:selected {
            background-color: #FCE4EC;
            color: #880E4F;
        }

        QRadioButton {
            spacing: 8px;
            color: #880E4F;
            padding: 2px 0;
        }
        QRadioButton::indicator {
            width: 14px;
            height: 14px;
            border-radius: 7px;
            border: 1px solid #FF69B4;
            background: #FFFFFF;
        }
        QRadioButton::indicator:checked {
            background-color: #FF1493;
            border: 2px solid #FFFFFF;
        }
    )");
}
