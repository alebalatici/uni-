//
// Created by Alexandra on 6/7/2026.
//

#ifndef MELODII_MY_TABLE_H
#define MELODII_MY_TABLE_H

#include <QAbstractTableModel>
#include <vector>
#include "../domain/melodie.h"
using std::vector;
class MyTable : public QAbstractTableModel
{
    private:
    vector<Melodie> melodii;
    vector<int> rank_frequencies;
    public:
    MyTable(const vector<Melodie>& _melodii, const vector<int>& _rank_frequencies) : melodii{_melodii}, rank_frequencies {_rank_frequencies} {};

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override
    {
        return melodii.size();
    }

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override
    {
        return 5;
    }


    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override
    {

        if (!index.isValid()) return QVariant();
        if (index.row() < 0 || index.row() > melodii.size() ) return QVariant();
        if (role == Qt::DisplayRole)
        {
            auto& m = melodii[index.row()];
            if (index.column() == 0) return QString::number(m.get_id());
            if (index.column() == 1) return QString::fromStdString(m.get_titlu());
            if (index.column() == 2) return QString::fromStdString(m.get_artist());
            if (index.column() == 3) return QString::number(m.get_rank());
            if (index.column() == 4)
            {
                return QString::number(rank_frequencies[m.get_rank()]);
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
                switch (section)
                {
                    case 0: return "Id"; break;
                    case 1: return "Titlu"; break;
                    case 2: return "Artist"; break;
                    case 3: return "Rank"; break;
                    default: break;
                }
            }

            else if (orientation == Qt::Vertical)
            {
                return section + 1;
            }
        }
        return QVariant();
    }

    void setData(const vector<Melodie>& _melodii, const vector<int>& _rank_frequencies)
    {
        beginResetModel();
        melodii = _melodii;
        rank_frequencies = _rank_frequencies;
        endResetModel();
    }

    Melodie getMelodieAt(int row)
    {
        return melodii[row];
    }
};

#endif //MELODII_MY_TABLE_H
