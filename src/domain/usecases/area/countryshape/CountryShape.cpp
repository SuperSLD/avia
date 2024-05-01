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
        regions.append(region);
    }

    qDebug() << minLon << maxLon << minLat << maxLat;
}

bool CountryShape::pointInCountry(double lon, double lat) {
    auto sumResult = false;
    foreach(auto region, regions) {
        auto result = false;
        int j = region.size() - 1;
        for (int i = 0; i < region.size(); i++) {
            if ( (region[i][1] < lat && region[j][1] >= lat || region[j][1] < lat && region[i][1] >= lat) &&
                 (region[i][0] + (lat - region[i][1]) / (region[j][1] - region[i][1]) * (region[j][0] - region[i][0]) < lon) )
                result = !result;
            j = i;
        }
        if (result) sumResult = true;
    }
    return sumResult;
}
