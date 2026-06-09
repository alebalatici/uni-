//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_GUI_H
#define TASKS_GUI_H

#include <QWidget>
#include <QtWidgets>

#include "my_list_string.h"
#include "my_table.h"
#include "../observer/observer.h"
#include "../service/srv_tasks.h"
class GraphicalInterface : public QWidget, public Observer{
private:
    ServiceTasks& srv;

    QTableView* table_tasks = nullptr;
    MyTable* model_table = nullptr;

    QLineEdit* edit_id = nullptr;
    QLineEdit* edit_descriere = nullptr;
    QLineEdit* edit_programatori = nullptr;
    QLineEdit* edit_stare = nullptr;
    QLineEdit* edit_search = nullptr;

    QPushButton* button_adaugare = nullptr;

    QVBoxLayout* layout_left = nullptr;
    QVBoxLayout* layout_right = nullptr;

    QListView* list_tasks = nullptr;
    MyListString* model_list = nullptr;

    void initialize_table(QVBoxLayout* layout)
    {
        QGroupBox* table = new QGroupBox;
        QVBoxLayout* layout_table = new QVBoxLayout;
        table->setLayout(layout_table);

        table_tasks->setSelectionBehavior(QAbstractItemView::SelectRows);
        table_tasks->setSelectionMode(QAbstractItemView::SingleSelection);

        layout_table->addWidget(table_tasks);
        layout->addWidget(table);
    }

    void initialize_form_adaugare(QVBoxLayout* layout)
    {
        QGroupBox* adaugare = new QGroupBox("Adaugare");
        QVBoxLayout* layout_adaugare = new QVBoxLayout;
        adaugare->setLayout(layout_adaugare);

        edit_id = new QLineEdit;
        edit_descriere = new QLineEdit;
        edit_programatori = new QLineEdit;
        edit_stare = new QLineEdit;

        QFormLayout* form_adaugare = new QFormLayout;

        form_adaugare->addRow(new QLabel("Id:"), edit_id);
        form_adaugare->addRow(new QLabel("Descriere:"), edit_descriere);
        form_adaugare->addRow(new QLabel("Stare:"), edit_stare);
        form_adaugare->addRow(new QLabel("Programatori:"), edit_programatori);

        button_adaugare = new QPushButton("Adaugare");
        form_adaugare->addRow(button_adaugare);

        layout_adaugare->addLayout(form_adaugare);
        layout->addWidget(adaugare);
    }

    void initialize_search_programator(QVBoxLayout* layout)
    {
        QGroupBox* search = new QGroupBox("Search");
        QVBoxLayout* layout_search = new QVBoxLayout;
        search->setLayout(layout_search);

        edit_search = new QLineEdit;
        layout_search->addWidget(edit_search);

        layout->addWidget(search);
    }

    /**
     * Optional
     * @param layout Layout-ul in care pun lista
     */
    void initialize_list(QVBoxLayout* layout)
    {
        QGroupBox* list = new QGroupBox;
        QVBoxLayout* layout_list = new QVBoxLayout;
        list->setLayout(layout_list);

        list_tasks->setSelectionBehavior(QAbstractItemView::SelectRows);
        list_tasks->setSelectionMode(QAbstractItemView::SingleSelection);

        layout_list->addWidget(list_tasks);
        layout->addWidget(list);
    }

    void initialize_gui_components()
    {
        QHBoxLayout* layout_main = new QHBoxLayout;
        setLayout(layout_main);

        QGroupBox* left = new QGroupBox;
        layout_left = new QVBoxLayout;
        left->setLayout(layout_left);

        QGroupBox* right = new QGroupBox;
        layout_right = new QVBoxLayout;
        right->setLayout(layout_right);

        initialize_table(layout_left);
        initialize_form_adaugare(layout_right);
        initialize_search_programator(layout_right);
        initialize_list(layout_right);

        layout_main->addWidget(left);
        layout_main->addWidget(right);
    }

    void connect_signals_slots()
    {
        QObject::connect(button_adaugare, &QPushButton::clicked, this, [this]()
        {
            try
            {
                int id = edit_id->text().toInt();
                string descriere = edit_descriere->text().toStdString();
                string stare = edit_stare->text().toStdString();
                string programatori_string = edit_programatori->text().toStdString();

                edit_id->clear();
                edit_descriere->clear();
                edit_programatori->clear();
                edit_stare->clear();

                vector<string> programatori = ServiceTasks::getVectorProgrammers(programatori_string);
                srv.addTask(id, descriere, programatori, stare);
                reload_data(srv.getTasks());
                QMessageBox::information(this, "Info", "Added task successfully");
            }
            catch (std::exception& e)
            {
                QMessageBox::warning(this, "Error", e.what());
            }
        });

        QObject::connect(edit_search, &QLineEdit::textChanged, this, [this]()
        {
            string text = edit_search->text().toStdString();
            reload_data(ServiceTasks::filterByString(text, srv.getTasks()));
        });

        QObject::connect(table_tasks, &QTableView::clicked, this, [this]()
        {
            auto selected_rows = table_tasks->selectionModel()->selectedRows();
            if (selected_rows.empty())
            {
                QMessageBox::warning(this, "Warning", "No tasks selected");
                return;
            }
            auto first_selected_row = selected_rows.at(0);
            int row = first_selected_row.row();
            auto t = model_table->getTaskAt(row);
            reload_data_list(t.getProgramatori());
        });
    }

    void reload_data(const vector<Task>& tasks)
    {
        model_table->setTasks(ServiceTasks::sortByStare(tasks));
    }

    void reload_data_list(const vector<string>& programmers)
    {
        model_list->setProgrammers(programmers);
    }

public:
    void update() override
    {
        reload_data(srv.getTasks());
    }

    GraphicalInterface(ServiceTasks& _srv) : srv{_srv}
    {
        table_tasks = new QTableView;
        model_table = new MyTable(srv.getTasks());
        table_tasks->setModel(model_table);

        list_tasks = new QListView;
        model_list = new MyListString();
        list_tasks->setModel(model_list);

        initialize_gui_components();
        connect_signals_slots();
        reload_data(srv.getTasks());

        srv.addObserver(this);
    }

    ~GraphicalInterface() override
    {
        srv.removeObserver(this);
    }
};

#endif //TASKS_GUI_H