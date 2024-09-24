//
// Created by Леонид Соляной on 27.04.2024.
//

#include "OSMDirectionModel.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

OSMDirectionModel::OSMDirectionModel(QJsonValue val) {
    auto object = val.toObject();

    isValid = !object.contains("error") && object.contains("routes");

    if (isValid) {
        auto summary = object["routes"].toArray()[0].toObject()["legs"].toObject();
        this->distance = object["routes"].toArray()[0].toObject()["legs"].toArray()[0].toObject()["distance"].toDouble() / 1000;
        // время в пути в секундах переделываем в часы
        this->duration = object["routes"].toArray()[0].toObject()["legs"].toArray()[0].toObject()["duration"].toDouble() / 60 / 60;
    }
}
