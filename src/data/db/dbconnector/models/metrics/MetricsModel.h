//
// Created by Леонид Соляной on 13.05.2024.
//

#ifndef AVIA_METRICSMODEL_H
#define AVIA_METRICSMODEL_H


#include "src/domain/models/analytics/BaseAnalyticModel.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/domain/models/area/Area.h"

class MetricsModel: public BaseAnalyticModel {

private:

    QList<ChartLine> nonStraightnessBarChart;

    QList<QList<QString>> aircraftModelsTable;

public:

    MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area);
    MetricsModel() {}

    QList<AnalyticsRow> getRows(bool isSingle = true) override;
};


#endif //AVIA_METRICSMODEL_H
