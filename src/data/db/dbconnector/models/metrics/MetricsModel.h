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
    /// график времени
    QList<ChartLine> timeBarChart;
    /// график критерия для хабов
    QList<ChartLine> hubBarChart;
    QString maxHubSave;
    QList<QString> maxHubSaveValues;
    /// график критерия не для хабов
    QList<ChartLine> notHubBarChart;
    QString maxNotHubSave;
    QList<QString> maxNotHubSaveValues;
    /// график зависимости крит функции от жадности и стадности
    QList<ChartLine> hubByGreedLineChart;
    QList<ChartLine> notHubByGreedLineChart;

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

    /// таблица всех самолетов в парках
    QList<QList<QString>> aircraftModelsTable;
    /// таблица сравнения показателей парков
    QList<QList<QString>> parkDiffTable;

    /// название оптимального графа
    QString optimalSave;
    /// таблица данных о лучшем парке
    QList<QList<QString>> optimalParkTable;
    /// диаграмма типов парка
    QList<ChartLine> optimalTypesPieChart;

public:

    MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area);
    MetricsModel() {}

    QList<AnalyticsRow> getRows(bool isSingle = true) override;
};


#endif //AVIA_METRICSMODEL_H
