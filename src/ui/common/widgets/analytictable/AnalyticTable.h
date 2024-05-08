//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_ANALYTICTABLE_H
#define AVIA_ANALYTICTABLE_H


#include <QFrame>
#include "src/domain/models/analytics/AnalyticsModel.h"

class AnalyticTable: public QFrame {

private:
    QVBoxLayout *rowsContainer;
    BaseAnalyticModel *analyticsModel;

public:
    AnalyticTable();
    ~AnalyticTable();

    void setAnalytics(BaseAnalyticModel *analytics);
    void setAnalytics(QList<AnalyticsRow> rows);
    void clearList(QLayout *list);
};


#endif //AVIA_ANALYTICTABLE_H
