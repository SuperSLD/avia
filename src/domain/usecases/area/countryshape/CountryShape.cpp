//
// Created by Леонид Соляной on 28.04.2024.
//

#include "CountryShape.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

CountryShape::CountryShape(QString name) {
    QFile file;
    file.setFileName(":/resc/resc/jsondata/" + name + ".json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto val = file.readAll();
    auto russia = QJsonDocument::fromJson(val);
    file.close();

    foreach(auto district, russia.object().keys()) {
        auto districtPointsArray = russia[district].toObject()["0"].toArray();
        foreach(auto districtPoint, districtPointsArray) {
            auto lon = districtPoint[0].toDouble();
            auto lat = districtPoint[1].toDouble();

            if (lon > maxLon) maxLon = lon;
            if (lon < minLon) minLon = lon;
            if (lat > maxLat) maxLat = lat;
            if (lat < minLat) minLat = lat;
        }
    }
}
