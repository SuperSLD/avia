//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_LINECHARTWIDGET_H
#define AVIA_LINECHARTWIDGET_H


#include <QFrame>
#include "src/domain/models/analytics/view/chart/ChartLine.h"

class LineChartWidget: public QFrame {
    Q_OBJECT

private:
    int h;
    QList<ChartLine> lines;

    bool shortLabels;

    QString getLabel(double val);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    LineChartWidget(int h, QList<ChartLine> lines);
    ~LineChartWidget();
};


#endif //AVIA_LINECHARTWIDGET_H
