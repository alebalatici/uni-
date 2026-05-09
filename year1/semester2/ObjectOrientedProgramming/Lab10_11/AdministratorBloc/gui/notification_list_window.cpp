#include "notification_list_window.h"

#include <QFormLayout>
#include <QMessageBox>

void NotificationListWindow::notification_list_window_initialize_components()
{
    QHBoxLayout *layout_main = new QHBoxLayout;
    this->setLayout(layout_main);

    QWidget* left = new QWidget;
    QVBoxLayout* layout_left = new QVBoxLayout;
    left->setLayout(layout_left);

    QWidget* right = new QWidget;
    QVBoxLayout* layout_right = new QVBoxLayout;
    right->setLayout(layout_right);

    notification_list_window_initialize_form_adaugare(layout_left);
    notification_list_window_initialize_form_empty(layout_left);
    notification_list_window_initialize_form_adaugare_random(layout_left);
    notification_list_window_initialize_form_export(layout_left);
    notification_list_window_initialize_table(layout_right);

    layout_main->addWidget(left);
    layout_main->addWidget(right);
}

void NotificationListWindow::notification_list_window_initialize_form_adaugare(QVBoxLayout *layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_adaugare->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    layout_form->addRow(label_apartament_adaugare, edit_apartament_adaugare);
    layout_form->addRow(button_add_locatar);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_adaugare);
}

void NotificationListWindow::notification_list_window_initialize_form_empty(QVBoxLayout *layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_golire->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    layout_form->addRow(button_empty_list);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_golire);
}

void NotificationListWindow::notification_list_window_initialize_form_adaugare_random(QVBoxLayout *layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_adaugare_random->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    layout_form->addRow(label_apartament_adaugare_random, edit_apartament_adaugare_random);
    layout_form->addRow(button_add_locatar_random);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_adaugare_random);
}

void NotificationListWindow::notification_list_window_initialize_form_export(QVBoxLayout *layout)
{
    QVBoxLayout* layout_box = new QVBoxLayout;
    this->group_box_export->setLayout(layout_box);
    QFormLayout* layout_form = new QFormLayout;
    layout_form->addRow(label_export_filename, edit_export_filename);
    layout_form->addRow(button_export);
    layout_box->addLayout(layout_form);
    layout->addWidget(group_box_export);
}

void NotificationListWindow::notification_list_window_initialize_table(QVBoxLayout *layout)
{
    int nr_lines = 4;
    int nr_columns = 0;
    this->notification_list_table = new QTableWidget(nr_columns, nr_lines);
    QStringList table_header_list;
    table_header_list << "Apartament" << "Nume" << "Suprafata" << "Tip";
    this->notification_list_table->setHorizontalHeaderLabels(table_header_list);
    this->notification_list_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    layout->addWidget(notification_list_table);
}

void NotificationListWindow::notification_list_window_connect_signals_slots()
{
    QObject::connect(button_add_locatar, &QPushButton::clicked, this, &NotificationListWindow::notification_list_window_add_locatar);
    QObject::connect(button_empty_list, &QPushButton::clicked, this, &NotificationListWindow::notification_list_window_empty_list);
    QObject::connect(button_add_locatar_random, &QPushButton::clicked, this, &NotificationListWindow::notification_list_window_add_random_notificari);
    QObject::connect(button_export, &QPushButton::clicked, this, &NotificationListWindow::notification_list_window_export_to_html);
}

void NotificationListWindow::reload_notification_list_data(vector<Locatar> notificari)
{
    this->notification_list_table->clearContents();
    this->notification_list_table->setRowCount(int(notificari.size()));

    int line_number = 0;
    for (auto &locatar : notificari)
    {
        this->notification_list_table->setItem(line_number, 0, new QTableWidgetItem(QString::number(locatar.get_apartment())));
        this->notification_list_table->setItem(line_number, 1, new QTableWidgetItem(QString::fromStdString(locatar.get_nume())));
        this->notification_list_table->setItem(line_number, 2, new QTableWidgetItem(QString::number(locatar.get_suprafata())));
        this->notification_list_table->setItem(line_number, 3, new QTableWidgetItem(QString::fromStdString(locatar.get_tip())));
        line_number++;
    }
}

void NotificationListWindow::notification_list_window_add_locatar()
{
    try
    {
        int apartament = edit_apartament_adaugare->text().toInt();
        edit_apartament_adaugare->clear();

        this->srv.list_add_notificare(apartament);
        this->reload_notification_list_data(this->srv.list_get_all_notificari());
        QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes in lista de notificari."));
    }

    catch (ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void NotificationListWindow::notification_list_window_empty_list()
{
    try
    {
        this->srv.list_empty_full();
        this->reload_notification_list_data(this->srv.list_get_all_notificari());
    }

    catch (ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void NotificationListWindow::notification_list_window_add_random_notificari()
{
    try
    {
        int number = edit_apartament_adaugare_random->text().toInt();
        edit_apartament_adaugare_random->clear();

        this->srv.list_add_random_notificari(number);
        this->reload_notification_list_data(this->srv.list_get_all_notificari());
        QMessageBox::information(this, "Info", QString::fromStdString("Locatari adaugati cu succes."));
    }

    catch (ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}

void NotificationListWindow::notification_list_window_export_to_html()
{
    try
    {
        string filename = edit_export_filename->text().toStdString();
        edit_export_filename->clear();

        srv.list_export_to_html(filename);

        QMessageBox::information(this, "Info", QString::fromStdString("Lista de notificari a fost exportata cu succes."));
    }

    catch (ServiceException& e)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(e.get_msg()));
    }
}