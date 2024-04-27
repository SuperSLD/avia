//
// Created by Леонид Соляной on 27.04.2024.
//

#ifndef AVIA_OSMVERSIONSMODEL_H
#define AVIA_OSMVERSIONSMODEL_H


#include <QString>
#include <QJsonValue>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

class OSMVersionsModel: public BaseModel{

public:
    QString version;
    QString generator;

    OSMVersionsModel() {};
    OSMVersionsModel(QJsonValue obj);
};


#endif //AVIA_OSMVERSIONSMODEL_H
