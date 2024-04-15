//
// Created by Леонид Соляной on 15.04.2024.
//

#ifndef AVIA_CHARTANALYTICSCELL_H
#define AVIA_CHARTANALYTICSCELL_H


#include "src/domain/models/analytics/view/BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/chart/ChartCellWidget.h"
#include "ChartLine.h"

#include <QList>

class ChartAnalyticsCell: public BaseAnalyticsCell {

public:
    QString type;
    QString name;
    QList<ChartLine> lines;

    ChartAnalyticsCell(
            QString type,
            QString name,
            QList<ChartLine> lines
    ) {
        this->type = type;
        this->name = name;
        this->lines = lines;
    }

    ChartAnalyticsCell() {}

    QWidget* getView() override {
        return new ChartCellWidget(type, name, lines);
    }
};

#endif //AVIA_CHARTANALYTICSCELL_H
