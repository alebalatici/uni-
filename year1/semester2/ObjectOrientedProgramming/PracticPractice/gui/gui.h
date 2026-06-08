//
// Created by Alexandra on 6/7/2026.
//

#ifndef MELODII_GUI_H
#define MELODII_GUI_H

#include <QWidget>
#include <QtWidgets>

#include "histogram_widget.h"
#include "my_table.h"
#include "../service/service_melodii.h"

class GraphicalInterface : public QWidget
{
private:
    ServiceMelodii& srv;

    QTableView* table_melodii = nullptr;
    MyTable* model_melodii = nullptr;

    QLineEdit* edit_titlu = nullptr;
    QSlider* slider_rank = nullptr;
    QLabel* label_slider = nullptr;
    QPushButton* button_update = nullptr;
    QPushButton* button_delete = nullptr;

    void initialize_table(QVBoxLayout* layout)
    {
        QGroupBox* table = new QGroupBox;
        QVBoxLayout* layout_table = new QVBoxLayout;
        table->setLayout(layout_table);

        table_melodii->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout_table->addWidget(table_melodii);
        layout->addWidget(table);
    }

    void initialize_gui_components()
    {
        QHBoxLayout* layout_main = new QHBoxLayout;
        setLayout(layout_main);

        QGroupBox* left = new QGroupBox;
        QVBoxLayout* layout_left = new QVBoxLayout;
        left->setLayout(layout_left);

        QGroupBox* right = new QGroupBox;
        QVBoxLayout* layout_right = new QVBoxLayout;
        right->setLayout(layout_right);

        initialize_table(layout_left);

        edit_titlu = new QLineEdit;
        layout_left->addWidget(edit_titlu);
        slider_rank = new QSlider(Qt::Horizontal);
        slider_rank->setRange(0, 10);
        layout_left->addWidget(slider_rank);
        label_slider = new QLabel;
        layout_left->addWidget(label_slider);

        button_update = new QPushButton("Update Melodie");
        layout_left->addWidget(button_update);

        button_delete = new QPushButton("Delete Melodie");
        layout_right->addWidget(button_delete);

        HistogramWidget* histogram = new HistogramWidget(srv);
        histogram->setMinimumWidth(500);
        layout_right->addWidget(histogram);

        layout_main->addWidget(left);
        layout_main->addWidget(right);
    }

    void reload_data(const vector<Melodie>& melodii)
    {
        model_melodii->setData(srv.sort_by_rank(melodii), srv.get_rank_frequencies(melodii));
    }

    void connect_signals_slots()
    {
        QObject::connect(slider_rank, &QSlider::valueChanged, this, [this] ()
        {
            int value = slider_rank->value();
            label_slider->setText("Slider value: " + QString::number(value));
        });

        QObject::connect(table_melodii, &QTableView::clicked, this, [this] ()
        {
            auto index = table_melodii->currentIndex();
            int row = index.row();
            Melodie m = model_melodii->getMelodieAt(row);
            edit_titlu->setText(QString::fromStdString(m.get_titlu()));
        });

        QObject::connect(button_update, &QPushButton::clicked, this, [this] ()
        {
            auto selected_indexes = table_melodii->selectionModel()->selectedIndexes();
            if (selected_indexes.empty())
            {
                QMessageBox::warning(this, "Error", "No row selected");
                return;
            }
            auto index = selected_indexes.at(0);
            int row = index.row();
            Melodie m = model_melodii->getMelodieAt(row);

            string titlu_nou = edit_titlu->text().toStdString();
            int rank_nou = slider_rank->value();

            srv.modify_melodie(m.get_id(), titlu_nou, m.get_artist(), rank_nou);
            reload_data(srv.get_all_melodii());
            QMessageBox::information(this, "Info", "Modified song successfully!");
        });

        QObject::connect(button_delete, &QPushButton::clicked, this, [this] ()
        {
            auto selected_indexes = table_melodii->selectionModel()->selectedIndexes();
            if (selected_indexes.empty())
            {
                QMessageBox::warning(this, "Error", "No row selected");
            }
            auto index = selected_indexes.at(0);
            int row = index.row();
            Melodie m = model_melodii->getMelodieAt(row);
            if (srv.get_artist_song_count(srv.get_all_melodii())[m.get_artist()] == 1)
            {
                QMessageBox::warning(this, "Error", "Artist only has one song in this table!");
                return;
            }
            srv.delete_melodie(m.get_id());
            reload_data(srv.get_all_melodii());
            QMessageBox::information(this, "Info", "Deleted song successfully!");
        });
    }

public:
    GraphicalInterface(ServiceMelodii& _srv) : srv{_srv}
    {
        table_melodii = new QTableView;
        table_melodii->setSelectionMode(QAbstractItemView::SingleSelection);
        table_melodii->setSelectionBehavior(QAbstractItemView::SelectRows);

        model_melodii = new MyTable(srv.get_all_melodii(), srv.get_rank_frequencies(srv.get_all_melodii()));
        table_melodii->setModel(model_melodii);

        initialize_gui_components();
        connect_signals_slots();
        reload_data(srv.get_all_melodii());
    }
};



#endif //MELODII_GUI_H
