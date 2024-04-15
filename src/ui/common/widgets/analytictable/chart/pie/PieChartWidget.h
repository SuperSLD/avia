//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_PIECHARTWIDGET_H
#define AVIA_PIECHARTWIDGET_H


#include <QFrame>
#include "src/domain/models/analytics/view/chart/ChartLine.h"

class PieChartWidget: public QFrame {
    Q_OBJECT

private:
    int h;
    QString type;
    QList<ChartLine> lines;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    PieChartWidget(int h, QString type, QList<ChartLine> lines);
    ~PieChartWidget();
};


#endif //AVIA_PIECHARTWIDGET_H
