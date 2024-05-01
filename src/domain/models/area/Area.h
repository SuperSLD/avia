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
    double maxDistance = 0;

    Area(QList<QList<AreaPoint>> points) {
        this->points = points;
        foreach(auto line, points) {
            foreach(auto point, line) {
                if (point.distance > maxDistance) {
                    maxDistance = point.distance;
                }
            }
        }
    }

    Area() {}
};

#endif //AVIA_AREA_H
