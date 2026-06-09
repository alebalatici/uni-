//
// Created by Alexandra on 6/9/2026.
//

#ifndef TASKS_MY_LIST_H
#define TASKS_MY_LIST_H

#include <string>
#include <vector>
#include <QAbstractListModel>

using std::string;
using std::vector;
class MyListString : public QAbstractListModel {
private:
    vector<string> programmers;
public:
    MyListString(vector<string> _programmers = {}) : programmers{std::move(_programmers)} {}

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override
    {
        Q_UNUSED(parent)
        return static_cast<int>(programmers.size());
    }

    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override
    {
        if (!index.isValid())
        {
            return {};
        }

        if (index.row() < 0 || index.row() >= programmers.size())
        {
            return {};
        }

        const auto& p = programmers[index.row()];
        if (role == Qt::DisplayRole)
        {
            QString text = QString("%1").arg(QString::fromStdString(p));
            return text;
        }

        return {};
    }

    void setProgrammers(const vector<string>& _programmers)
    {
        beginResetModel();
        programmers = _programmers;
        endResetModel();
    }
};

#endif //TASKS_MY_LIST_H
