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
        QList<QList<double>> region;
        auto p = russia[district].toObject()["p"].toDouble();
        auto districtPointsArray = russia[district].toObject()["0"].toArray();
        foreach(auto districtPoint, districtPointsArray) {
            auto lon = districtPoint[1].toDouble();
            auto lat = districtPoint[0].toDouble();

            if (lon > maxLon) maxLon = lon;
            if (lon < minLon) minLon = lon;
            if (lat > maxLat) maxLat = lat;
            if (lat < minLat) minLat = lat;
            region.append(QList<double> {
                lon, lat
            });
        }
        regions.append(QPair<double, QList<QList<double>>>(p, region));
    }

    qDebug() << minLon << maxLon << minLat << maxLat;
}

double CountryShape::pointInCountry(double lon, double lat) {
    auto p = -1.0;
    foreach(auto region, regions) {
        auto result = false;
        int j = region.second.size() - 1;
        for (int i = 0; i < region.second.size(); i++) {
            if ( (region.second[i][1] < lat && region.second[j][1] >= lat || region.second[j][1] < lat && region.second[i][1] >= lat) &&
                 (region.second[i][0] + (lat - region.second[i][1]) / (region.second[j][1] - region.second[i][1]) * (region.second[j][0] - region.second[i][0]) < lon) )
                result = !result;
            j = i;
        }
        if (result) {
            p = region.first;
        }
    }
    return p;
}
