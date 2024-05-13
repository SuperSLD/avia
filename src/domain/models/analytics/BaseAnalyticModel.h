//
// Created by Леонид Соляной on 06.05.2024.
//

#ifndef AVIA_BASEANALYTICMODEL_H
#define AVIA_BASEANALYTICMODEL_H

#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/domain/models/analytics/view/AnalyticsRow.h"

class BaseAnalyticModel: public BaseModel {

public:
    BaseAnalyticModel() {};
    ~BaseAnalyticModel() {};

    virtual QList<AnalyticsRow> getRows(bool isSingle = true) { return QList<AnalyticsRow>(); };
};

#endif //AVIA_BASEANALYTICMODEL_H
