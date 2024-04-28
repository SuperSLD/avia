//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_TRANSPORTGRAPHMODEL_H
#define AVIA_TRANSPORTGRAPHMODEL_H


#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"

class TransportGraphModel: public BaseModel {

public:
    QList<AirportModel> airports;

    TransportGraphModel(QList<AirportModel> airports);
    TransportGraphModel() {}

    TransportGraphModel getWithEmptyEdges();

    AirportModel getMinDistanceAirport(double lon, double lat);
};


#endif //AVIA_TRANSPORTGRAPHMODEL_H
