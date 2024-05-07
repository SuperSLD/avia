//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_TRANSPORTGRAPHMODEL_H
#define AVIA_TRANSPORTGRAPHMODEL_H


#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/models/analytics/BaseAnalyticModel.h"

class TransportGraphModel: public BaseAnalyticModel {

private:
    void calcDataForView();

public:
    QList<AirportModel> airports;
    int maxAirportFlightCount = 0;
    QList<QList<double>> viewLines;

    /// жадность
    double greed = 1.0;
    /// стадность
    double gregariousness = 1.0;

    TransportGraphModel(QList<AirportModel> airports, double greed = 1.0, double gregariousness = 1.0);
    TransportGraphModel(QJsonObject json);
    TransportGraphModel() {}

    TransportGraphModel getWithEmptyEdges();

    AirportModel getMinDistanceAirport(double lon, double lat);
    AirportModel findAirport(QString id);

    QJsonObject toJson() override;

    QList<AnalyticsRow> getRows() override;
};


#endif //AVIA_TRANSPORTGRAPHMODEL_H
