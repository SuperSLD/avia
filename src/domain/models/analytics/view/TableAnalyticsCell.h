//
// Created by Леонид Соляной on 15.05.2024.
//

#ifndef AVIA_TABLEANALYTICSCELL_H
#define AVIA_TABLEANALYTICSCELL_H

#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/table/TableCellWidget.h"

class TableAnalyticsCell: public BaseAnalyticsCell {

public:
    QList<QList<QString>> table;
    bool firstIsBig;

    TableAnalyticsCell(
            QList<QList<QString>> table,
            bool firstIsBig = false
    ) {
        this->table = table;
        this->firstIsBig = firstIsBig;
    }

    TableAnalyticsCell() {}

    QWidget *getView() override {
        return new TableCellWidget(table, firstIsBig);
    }
};

#endif //AVIA_TABLEANALYTICSCELL_H
