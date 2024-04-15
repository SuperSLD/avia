//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_CHARTCELLWIDGET_H
#define AVIA_CHARTCELLWIDGET_H


#include <QFrame>
#include "src/domain/models/analytics/view/chart/ChartLine.h"

class ChartCellWidget: public QFrame {
    Q_OBJECT

public:
    ChartCellWidget(
        QString type,
        QString name,
        QList<ChartLine> lines
    );
    ~ChartCellWidget();

};


#endif //AVIA_CHARTCELLWIDGET_H
