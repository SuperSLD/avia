//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_BASEANALYTICSCELL_H
#define AVIA_BASEANALYTICSCELL_H

#include <QString>
#include <QWidget>

class BaseAnalyticsCell {
public:
    BaseAnalyticsCell() {}

    virtual QWidget* getView() {};
};

#endif //AVIA_BASEANALYTICSCELL_H
