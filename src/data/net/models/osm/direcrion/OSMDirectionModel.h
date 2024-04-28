//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_OSMDIRECTIONMODEL_H
#define AVIA_OSMDIRECTIONMODEL_H


#include <QString>
#include <QJsonValue>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

class OSMDirectionModel: public BaseModel{

public:
    bool isValid;
    double distance;
    double duration;

    OSMDirectionModel() {};
    OSMDirectionModel(QJsonValue val);
};


#endif //AVIA_OSMDIRECTIONMODEL_H
