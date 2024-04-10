//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_NUMBERANALYTICSCELL_H
#define AVIA_NUMBERANALYTICSCELL_H


#include <QString>
#include <QList>
#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/numbercell/NumberCellWidget.h"

class NumberAnalyticsCell: public BaseAnalyticsCell {

public:
    QString value;
    QString name;
    QString color;

    NumberAnalyticsCell(
        QString value,
        QString name,
        QString color
    ) {
        this->value = value;
        this->name = name;
        this->color = color;
    }

    NumberAnalyticsCell() {}

    QWidget* getView() override {
        return new NumberCellWidget(value, name, color);
    }
};


#endif //AVIA_NUMBERANALYTICSCELL_H
