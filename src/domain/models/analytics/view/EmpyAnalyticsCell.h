//
// Created by Леонид Соляной on 12.05.2024.
//

#ifndef AVIA_EMPYANALYTICSCELL_H
#define AVIA_EMPYANALYTICSCELL_H

#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/empty/EmptyCellWidget.h"

class EmptyAnalyticsCell: public BaseAnalyticsCell {

public:
    EmptyAnalyticsCell() {}

    QWidget* getView() override {
        return new EmptyCellWidget();
    }
};

#endif //AVIA_EMPYANALYTICSCELL_H
