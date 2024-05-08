//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_ANALYTICSMODEL_H
#define AVIA_ANALYTICSMODEL_H


#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/data/db/dbconnector/models/flightmodel/FlightModel.h"
#include "src/domain/models/analytics/view/AnalyticsRow.h"
#include "src/domain/models/analytics/view/chart/ChartLine.h"
#include "BaseAnalyticModel.h"
#include <QList>

class AnalyticsModel: public BaseAnalyticModel {

private:
    void createDataForCharts();

public:
    int allCount = 0;
    int inRussiaCount = 0;
    int notRussia = 0;

    QList<ChartLine> flightCountPieChart;
    QList<ChartLine> flightCountBarChart;
    QList<ChartLine> distanceLineChart;

    int sumOfTopAirports = 0;
    int percentOfTopAirports = 0;
    QHash<QString, int> airports;
    QList<int> airportsCount;
    QHash<QString, int> airportsOut;
    QList<int> airportsCountOut;
    QList<ChartLine> airportsPieChart;
    QList<ChartLine> airportsBarChart;

    AnalyticsModel(QList<FlightModel*> flights);
    AnalyticsModel() {};
    ~AnalyticsModel();

    QList<AnalyticsRow> getRows() override;
};


#endif //AVIA_ANALYTICSMODEL_H
