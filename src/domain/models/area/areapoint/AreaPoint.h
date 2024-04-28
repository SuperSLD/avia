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
    QString distance;
    QString duration;
    bool isValid;

    AreaPoint(
        QString airportId,
        QString distance,
        QString duration
    ) {
        this->airportId = airportId;
        this->distance = distance;
        this->duration = duration;
        isValid = true;
    }

    AreaPoint(
        QString airportId
    ) {
        this->airportId = airportId;
        isValid = false;
    }
};

#endif //AVIA_AREAPOINT_H
