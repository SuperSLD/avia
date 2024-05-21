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

    /// график непрямолинейности
    QList<ChartLine> nonStraightnessBarChart;
    /// график плотности
    QList<ChartLine> plotBarChart;
    /// график количества типов
    QList<ChartLine> typesBarChart;
    /// график стоимости парка
    QList<ChartLine> costBarChart;
    /// график количества рейсов
    QList<ChartLine> flightBarChart;
    /// график зависимости стоимости от другого
    QList<ChartLine> costLineChart;
    /// график зависимости жадности от стоимости
    QList<ChartLine> greedLineChart;
    /// график зависимости стадности от стоимости
    QList<ChartLine> gregariousnessLineChart;

    QList<QList<QString>> aircraftModelsTable;
    QList<QList<QString>> parkDiffTable;

public:

    MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area);
    MetricsModel() {}

    QList<AnalyticsRow> getRows(bool isSingle = true) override;
};


#endif //AVIA_METRICSMODEL_H
