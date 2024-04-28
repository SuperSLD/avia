//
// Created by Леонид Соляной on 27.04.2024.
//

#include "OSMDirectionModel.h"

#include <QJsonObject>
#include <QJsonValue>

OSMDirectionModel::OSMDirectionModel(QJsonValue val) {
    auto object = val.toObject();

    isValid = !object.contains("error");

    if (isValid) {
        auto summary = object["routes"].toObject()["summary"].toObject();
        this->distance = summary["distance"].toDouble();
        this->duration = summary["duration"].toDouble();
    }

//    this->version = object["version"].toString();
//    this->generator = object["generator"].toString();
}
