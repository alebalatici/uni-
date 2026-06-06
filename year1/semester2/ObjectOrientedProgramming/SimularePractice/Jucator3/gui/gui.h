//
// Created by Alexandra on 5/18/2026.
//

#ifndef JUCATOR3_GUI_H
#define JUCATOR3_GUI_H
#include <QWidget>
#include <QtWidgets>
#include "../service/service_jucator.h"
class GraphicalInterface : public QWidget {
    private:
    ServiceJucator& srv;
    QTableWidget* table_jucatori{nullptr};
    QListWidget* list_jucatori{nullptr};

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

        main_layout->addWidget(left);
        main_layout->addWidget(right);
    }

    void connect_signals_slots()
    {

    }

    void initialize_table(QVBoxLayout* layout)
    {
        QGroupBox* table = new QGroupBox;
        QVBoxLayout* table_layout = new QVBoxLayout;
        table->setLayout(table_layout);

        table_jucatori = new QTableWidget(10, 4);

        QStringList header_jucatori;
        header_jucatori << "Nume" << "Tara" << "Numar Puncte" << "Rank";
        table_jucatori->setHorizontalHeaderLabels(header_jucatori);
        table_jucatori->setSelectionBehavior(QAbstractItemView::SelectRows);

        table_layout->addWidget(table_jucatori);
        layout->addWidget(table);
    }

    void reload_data_list(const vector<Jucator>& jucatori)
    {
        list_jucatori->clear();
        for (auto& j : jucatori)
        {
            QString text = QString("%1 | %2 | %3 | %4")
            .arg(QString::fromStdString(j.get_nume()))
            .arg(QString::fromStdString(j.get_tara()))
            .arg(QString::number(j.get_numar_puncte()))
            .arg(QString::number(j.get_ranking()));

            QListWidgetItem* item = new QListWidgetItem(text);
            list_jucatori->addItem(item);
        }
    }

    void initialize_list(QVBoxLayout* layout)
    {
        QGroupBox* list = new QGroupBox;
        QVBoxLayout* list_layout = new QVBoxLayout;
        list->setLayout(list_layout);

        list_jucatori = new QListWidget;
        list_jucatori->setSelectionBehavior(QAbstractItemView::SelectRows);

        list_layout->addWidget(list_jucatori);
        layout->addWidget(list);
    }

    void reload_data_table(const vector<Jucator>& jucatori)
    {
        table_jucatori->clearContents();
        table_jucatori->setRowCount(jucatori.size());
        int row = 0;
        for (auto& j : jucatori)
        {
            table_jucatori->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(j.get_nume())));
            table_jucatori->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(j.get_tara())));
            table_jucatori->setItem(row, 2, new QTableWidgetItem(QString::number(j.get_numar_puncte())));
            table_jucatori->setItem(row, 3, new QTableWidgetItem(QString::number(j.get_ranking())));
            row++;
        }
    }

    public:
    GraphicalInterface(ServiceJucator& _srv) : srv{_srv}
    {
        initialize_components();
        connect_signals_slots();
        reload_data_table(srv.get_all_jucatori());
        reload_data_list(srv.get_all_jucatori());
    }
};



#endif //JUCATOR3_GUI_H
