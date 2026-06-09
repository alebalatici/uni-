//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_TASK_WINDOWS_H
#define TASKS_TASK_WINDOWS_H

#include <QWidget>
#include <utility>
#include <QtWidgets>
#include "../observer/observer.h"
#include "../service/srv_tasks.h"

class TaskWindow : public Observer, public QWidget {
private:
    ServiceTasks& srv;
    string stare;

    QListWidget* lista = nullptr;

    QPushButton* button_open = nullptr;
    QPushButton* button_inprogress = nullptr;
    QPushButton* button_closed = nullptr;

    void reload_data(const vector<Task>& tasks)
    {
        lista->clear();

        vector<Task> filtered_tasks = ServiceTasks::filterByStare(stare, tasks);

        for (const auto& task : filtered_tasks)
        {
            lista->addItem(new QListWidgetItem(
            QString("%1 | %2 | %3 | %4")
            .arg(QString::number(task.getId()), QString::fromStdString(task.getDescriere()), QString::fromStdString(task.getStare()), QString::number(task.getProgramatori().size()))
            ));
        }
    }

    void initialize_task_window_components()
    {
        QVBoxLayout* layout = new QVBoxLayout;
        setLayout(layout);

        lista = new QListWidget;

        button_open = new QPushButton("Open");
        button_inprogress = new QPushButton("InProgress");
        button_closed = new QPushButton("Close");

        layout->addWidget(lista);
        layout->addWidget(button_open);
        layout->addWidget(button_inprogress);
        layout->addWidget(button_closed);
    }

    void connect_signals_slots()
    {
        QObject::connect(button_open, &QPushButton::clicked, this, [this]()
        {
            auto selected_item = lista->currentItem();
            if (selected_item == nullptr)
            {
                QMessageBox::warning(this, "Warning", "No row selected");
                return;
            }
            auto string_task = selected_item->text();
            int id = string_task.split("|").at(0).trimmed().toInt();
            srv.changeStare(id, "open");
            reload_data(srv.getTasks());
        });

        QObject::connect(button_closed, &QPushButton::clicked, this, [this]()
        {
            auto selected_item = lista->currentItem();
            if (selected_item == nullptr)
            {
                QMessageBox::warning(this, "Warning", "No row selected");
                return;
            }
            auto string_task = selected_item->text();
            int id = string_task.split("|").at(0).trimmed().toInt();
            srv.changeStare(id, "closed");
            reload_data(srv.getTasks());
        });

        QObject::connect(button_inprogress, &QPushButton::clicked, this, [this]()
        {
            auto selected_item = lista->currentItem();
            if (selected_item == nullptr)
            {
                QMessageBox::warning(this, "Warning", "No row selected");
                return;
            }
            auto string_task = selected_item->text();
            int id = string_task.split("|").at(0).trimmed().toInt();
            srv.changeStare(id, "inprogress");
            reload_data(srv.getTasks());
        });
    }

public:
    TaskWindow(ServiceTasks& _srv, string _stare) : srv{_srv}, stare{std::move(_stare)}
    {
        initialize_task_window_components();
        connect_signals_slots();
        reload_data(srv.getTasks());
        srv.addObserver(this);
    }

    ~TaskWindow() override
    {
        srv.removeObserver(this);
    }

    void update() override
    {
        reload_data(srv.getTasks());
    }
};

#endif //TASKS_TASK_WINDOWS_H
