//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_MY_TABLE_H
#define TASKS_MY_TABLE_H

#include <utility>
#include <vector>
#include <QAbstractTableModel>

#include "../domain/task.h"

using std::vector;
class MyTable : public QAbstractTableModel {
private:
    vector<Task> tasks;
public:
    MyTable(vector<Task> _tasks) : tasks{std::move(_tasks)} {}
    [[nodiscard]] int rowCount(const QModelIndex& parent) const override
    {
        return static_cast<int>(tasks.size());
    }

    [[nodiscard]] int columnCount(const QModelIndex& parent) const override
    {
        return 4;
    }

    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override
    {
        if (!index.isValid())
        {
            return {};
        }
        if (index.row() < 0 || index.row() >= tasks.size())
        {
            return {};
        }
        auto& t = tasks[index.row()];
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0) return QString::number(t.getId());
            if (index.column() == 1) return QString::fromStdString(t.getDescriere());
            if (index.column() == 2) return QString::fromStdString(t.getStare());
            if (index.column() == 3) return QString::number(t.getProgramatori().size());
        }
        return {};
    }

    [[nodiscard ]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal)
            {
                switch (section)
                {
                    case 0: return "Id";
                    case 1: return "Descriere";
                    case 2: return "Stare";
                    case 3: return "Numar Programatori";
                    default: break;
                }
            }
            else if (orientation == Qt::Vertical)
            {
                return section + 1;
            }
        }
        return {};
    }

    void setTasks(const vector<Task>& _tasks)
    {
        beginResetModel();
        tasks = _tasks;
        endResetModel();
    }

    Task getTaskAt(int row)
    {
        return tasks[row];
    }
};

#endif //TASKS_MY_TABLE_H
