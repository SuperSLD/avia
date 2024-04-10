//
// Created by Леонид Соляной on 11.04.2024.
//

#ifndef AVIA_TITLEANALYTICSCELL_H
#define AVIA_TITLEANALYTICSCELL_H

#include <QFrame>
#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/titlecell/TitleCellWidget.h"

class TitleAnalyticsCell: public BaseAnalyticsCell {

public:
    QString title;

    TitleAnalyticsCell(
        QString title
    ) {
        this->title = title;
    }

    QWidget* getView() override {
        return new TitleCellWidget(title);
    }
};

#endif //AVIA_TITLEANALYTICSCELL_H
