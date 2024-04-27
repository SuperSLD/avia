//
// Created by Леонид Соляной on 27.04.2024.
//

#include "OSMVersionsModel.h"

#include <QJsonObject>
#include <QJsonValue>

OSMVersionsModel::OSMVersionsModel(QJsonValue obj) {
    auto object = obj.toObject();
    this->version = object["version"].toString();
    this->generator = object["generator"].toString();
}
