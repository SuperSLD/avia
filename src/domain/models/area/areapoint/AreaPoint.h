//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREAPOINT_H
#define AVIA_AREAPOINT_H

#include <QString>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

class AreaPoint: public BaseModel {

public:
    QString airportId;
    double distance;
    double duration;
    bool isValid = false;
    double w;
    double h;
    double lon;
    double lat;

    AreaPoint(
        QString airportId,
        double distance,
        double duration,
        double w,
        double h,
        double lon,
        double lat
    ) {
        this->airportId = airportId;
        this->distance = distance;
        this->duration = duration;
        this->w = w;
        this->h = h;
        this->lon = lon;
        this->lat = lat;
        isValid = true;
    }

    AreaPoint(
        QString airportId
    ) {
        this->airportId = airportId;
        isValid = false;
    }

    AreaPoint() {};
};

#endif //AVIA_AREAPOINT_H
