//
// Created by Леонид Соляной on 09.04.2024.
//

#ifndef AVIA_ROUTEDATAMODEL_H
#define AVIA_ROUTEDATAMODEL_H

#include <QList>
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"
#include "src/data/db/dbconnector/models/flightmodel/flightdata/FlightDataModel.h"
#include "src/data/db/dbconnector/models/routemodel/routepoint/RoutePointModel.h"

class RouteDataModel: public BaseDBModel {

public:
    FlightDataModel current;
    QList<RoutePointModel> list;
    QString type;

    RouteDataModel(
        FlightDataModel current,
        QList<RoutePointModel> list,
        QString type
    );

    RouteDataModel();
};


#endif //AVIA_ROUTEDATAMODEL_H
