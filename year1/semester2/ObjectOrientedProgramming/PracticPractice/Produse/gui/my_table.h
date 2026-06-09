//
// Created by Alexandra on 6/7/2026.
//

#ifndef PRODUSE_MY_TABLE_H
#define PRODUSE_MY_TABLE_H

#include <QAbstractTableModel>
#include <qbrush.h>
#include <qcolor.h>
#include <vector>

#include "../domain/produs.h"
#include "../service/service_produs.h"

using std::vector;
class MyTable : public QAbstractTableModel {
    private:
    vector<Produs> produse;
    double pret = -1;
    public:
    MyTable(vector<Produs> _produse) : produse(_produse) {}

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override
    {
        return static_cast<int>(produse.size());
    }

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override
    {
        return 5;
    }

    void setPret(double _pret)
    {
        pret = _pret;

        auto top_left = index(0, 0);
        auto buttom_right = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);
        emit dataChanged(top_left, buttom_right, {Qt::BackgroundRole});
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
        {
            return {};
        }
        if (index.row() < 0 || index.row() >= produse.size())
        {
            return {};
        }
        auto& p = produse[index.row()];
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0) return QString::number(p.get_id());
            if (index.column() == 1) return QString::fromStdString(p.get_nume());
            if (index.column() == 2) return QString::fromStdString(p.get_tip());
            if (index.column() == 3) return QString::number(p.get_pret());
            if (index.column() == 4) return QString::number(ServiceProdus::count_vowels(p.get_nume()));
        }
        if (role == Qt::BackgroundRole)
        {
            if (pret != -1 && p.get_pret() <= pret)
            {
                return QBrush(Qt::red);
            }
        }
        return {};
    }

    void setProduse(vector<Produs> _produse)
    {
        beginResetModel();
        produse = _produse;
        endResetModel();
    }

};



#endif //PRODUSE_MY_TABLE_H
