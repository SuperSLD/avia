//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_FLIGHTMODEL_H
#define AVIA_FLIGHTMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"
#include "src/data/db/dbconnector/models/flightmodel/flightdata/FlightDataModel.h"

class FlightModel: public BaseDBModel {

public:
    QString id;
    QString passedTime;
    QString airport;
    QString type;
    FlightDataModel data;

    FlightModel(
            QString id,
            QString passedTime,
            QString airport,
            QString type,
            FlightDataModel data
    );

    FlightModel() {};

    QString getId() override;
    QList<PreviewItem> getPreview() override;
};


#endif //AVIA_FLIGHTMODEL_H
