//
// Created by Alexandra on 6/8/2026.
//

#ifndef PRODUSE_HISTOGRAM_WIDGET_H
#define PRODUSE_HISTOGRAM_WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <utility>

#include "../observer/observer.h"
#include "../service/service_produs.h"

class TypeWindow : public QWidget, public Observer {
    private:
    ServiceProdus& srv;
    string type;

    QLabel* count_label = nullptr;

    void initialize_components()
    {
        QVBoxLayout* layout = new QVBoxLayout;
        setLayout(layout);

        count_label = new QLabel;
        count_label->setAlignment(Qt::AlignCenter);
        count_label->setText(QString::number(srv.get_count_type(srv.get_all_produse())[type]));

        layout->addWidget(count_label);
    }

    public :
    TypeWindow(ServiceProdus& _srv, string _type) : srv(_srv), type{std::move(_type)}
    {
        initialize_components();

        srv.add_observer(this);
    }

    ~TypeWindow() override
    {
        srv.remove_observer(this);
    }

    void update() override
    {
        count_label->setText(QString::number(srv.get_count_type(srv.get_all_produse())[type]));
    }

};

#endif //PRODUSE_HISTOGRAM_WIDGET_H
