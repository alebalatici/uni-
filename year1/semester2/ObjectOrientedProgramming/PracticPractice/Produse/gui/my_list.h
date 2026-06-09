//
// Created by Alexandra on 6/7/2026.
//

#ifndef PRODUSE_MY_LIST_H
#define PRODUSE_MY_LIST_H

#include <QAbstractListModel>
#include <QWidget>
#include <vector>

#include "../domain/produs.h"
#include "../service/service_produs.h"

using std::vector;
class MyList : public QAbstractListModel {
    private:
    vector<Produs> produse;
    double pret = -1;
    public:
    MyList(const vector<Produs> &_produse) : produse(_produse) {}

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override
    {
        return static_cast<int>(produse.size());
    }

    void setPret(double _pret)
    {
        pret = _pret;

        auto top = index(0);
        auto buttom = index(rowCount(QModelIndex()) - 1);
        emit dataChanged(top, buttom, {Qt::BackgroundRole});
    }

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
        {
            return {};
        }
        if (index.row() >= produse.size())
        {
            return {};
        }
        auto& p = produse[index.row()];
        if (role == Qt::DisplayRole)
        {
            QString text = QString("%1 | %2 | %3 | %4 | %5")
            .arg(QString::number(p.get_id()))
            .arg(QString::fromStdString(p.get_nume()))
            .arg(QString::fromStdString(p.get_tip()))
            .arg(QString::number(p.get_pret()))
            .arg(QString::number(ServiceProdus::count_vowels(p.get_nume())));

            return text;
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

    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal)
            {
                return "Lista de Produse";
            }
        }
        return {};
    }

    void setProduse(const vector<Produs> &_produse)
    {
        beginResetModel();
        produse = _produse;
        endResetModel();
    }
};

#endif //PRODUSE_MY_LIST_H
