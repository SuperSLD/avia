//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREA_H
#define AVIA_AREA_H

#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"

#include <QList>

class Area: public BaseModel {

public:
    QList<QList<AreaPoint>> points;

    Area(QList<QList<AreaPoint>> points) {
        this->points = points;
    }
};

#endif //AVIA_AREA_H
