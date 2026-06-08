//
// Created by Alexandra on 6/7/2026.
//

#ifndef MELODII_HISTOGRAM_WIDGET_H
#define MELODII_HISTOGRAM_WIDGET_H

#include <QPainter>
#include <QWidget>

#include "../observer/observer.h"
#include "../service/service_melodii.h"

class HistogramWidget : public QWidget, public Observer
{
    Q_OBJECT
    private:
    ServiceMelodii& srv;

    public:
    HistogramWidget(ServiceMelodii& _srv) : srv{_srv}
    {
        srv.add_observer(this);
    }

    ~HistogramWidget() override
    {
        srv.remove_observer(this);
    }

    void update() override
    {
        QWidget::update();
    }

    protected:
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(this);

        int latime = width();
        int inaltime = height();

        int nr_bare = 11;
        int latime_bara = latime / nr_bare;

        for (int i = 0; i < nr_bare; i++)
        {
            int nr_melodii = srv.get_rank_frequencies(srv.get_all_melodii())[i];
            int inaltime_bara = 20 * nr_melodii;

            int x = i * latime_bara;
            int y = inaltime - inaltime_bara;

            painter.setBrush(Qt::blue);
            painter.drawRect(x, y, latime_bara - 5, inaltime_bara);
            painter.drawText(x + latime_bara / 3, inaltime - 5, QString::number(i));
        }

    }
};

#endif //MELODII_HISTOGRAM_WIDGET_H
