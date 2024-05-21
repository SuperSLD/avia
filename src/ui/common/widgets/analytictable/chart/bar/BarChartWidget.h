//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_BARCHARTWIDGET_H
#define AVIA_BARCHARTWIDGET_H


#include <QFrame>
#include "src/domain/models/analytics/view/chart/ChartLine.h"

class BarChartWidget: public QFrame {
    Q_OBJECT

private:
    int h;
    QList<ChartLine> lines;

    bool shortLabels;
    bool shortShortLabels;
    bool isSmall;

    QString getLabel(double val);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    BarChartWidget(int h, QList<ChartLine> lines);
    ~BarChartWidget();
};


#endif //AVIA_BARCHARTWIDGET_H
