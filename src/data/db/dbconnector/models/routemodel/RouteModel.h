//
// Created by Леонид Соляной on 09.04.2024.
//

#ifndef AVIA_ROUTEMODEL_H
#define AVIA_ROUTEMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"
#include "src/data/db/dbconnector/models/flightmodel/flightdata/FlightDataModel.h"
#include "src/data/db/dbconnector/models/routemodel/routedata/RouteDataModel.h"

class RouteModel: public BaseDBModel {

public:
    QString id;
    QString fnia;
    QString fid;
    RouteDataModel data;

    RouteModel(
            QString id,
            QString fnia,
            QString fid,
            RouteDataModel data
    );

    RouteModel() {};

    QString getId() override;
    QList<PreviewItem> getPreview() override;
};


#endif //AVIA_ROUTEMODEL_H
