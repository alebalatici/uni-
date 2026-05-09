#ifndef ADMINISTRATORBLOC_NOTIFICATION_LIST_WINDOW_H
#define ADMINISTRATORBLOC_NOTIFICATION_LIST_WINDOW_H
#include <QDialog>
#include <QGroupBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QObject>

#include "../service/service_locatari.h"

class NotificationListWindow : public QDialog {
    Q_OBJECT
    private:
    ServiceLocatari& srv;

    QTableWidget *notification_list_table;

    QLabel* label_apartament_adaugare = new QLabel("Numarul apartamentului:");
    QLabel* label_apartament_adaugare_random = new QLabel("Numarul de apartamente care sa fie adaugate:");
    QLabel* label_export_filename = new QLabel("Numele fisierului:");

    QLineEdit* edit_apartament_adaugare = new QLineEdit;
    QLineEdit* edit_apartament_adaugare_random = new QLineEdit;
    QLineEdit* edit_export_filename = new QLineEdit;

    QPushButton* button_add_locatar = new QPushButton("Adauga locatar");
    QPushButton* button_empty_list = new QPushButton("Goleste lista de notificari");
    QPushButton* button_add_locatar_random = new QPushButton("Adauga locatari random");
    QPushButton* button_export = new QPushButton("Export lista de notificari");


    QGroupBox* group_box_adaugare = new QGroupBox(tr("Adaugare"));
    QGroupBox* group_box_golire = new QGroupBox(tr("Goleste lista"));
    QGroupBox* group_box_adaugare_random = new QGroupBox(tr("Adaugare Random"));
    QGroupBox* group_box_export = new QGroupBox(tr("Export"));

    void notification_list_window_initialize_components();
    void notification_list_window_initialize_table(QVBoxLayout *layout);
    void notification_list_window_initialize_form_adaugare(QVBoxLayout *layout);
    void notification_list_window_initialize_form_empty(QVBoxLayout *layout);
    void notification_list_window_initialize_form_adaugare_random(QVBoxLayout *layout);
    void notification_list_window_initialize_form_export(QVBoxLayout *layout);
    void notification_list_window_connect_signals_slots();
    void reload_notification_list_data(vector<Locatar> notificari);

    public:
    NotificationListWindow(ServiceLocatari& _srv, QWidget* parent) : QDialog{parent}, srv{_srv}
    {
        notification_list_window_initialize_components();
        notification_list_window_connect_signals_slots();
        reload_notification_list_data(srv.list_get_all_notificari());
    }

    void notification_list_window_add_locatar();
    void notification_list_window_empty_list();
    void notification_list_window_add_random_notificari();
    void notification_list_window_export_to_html();
};



#endif //ADMINISTRATORBLOC_NOTIFICATION_LIST_WINDOW_H
