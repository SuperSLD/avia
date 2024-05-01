//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREAPOINT_H
#define AVIA_AREAPOINT_H

#include <QString>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

class AreaPoint: public BaseModel {

public:
    QString airportId;
    double distance;
    double duration;
    bool isValid = false;
    double w;
    double h;
    double lon;
    double lat;

    AreaPoint(
        QString airportId,
        double distance,
        double duration,
        double w,
        double h,
        double lon,
        double lat
    ) {
        this->airportId = airportId;
        this->distance = distance;
        this->duration = duration;
        this->w = w;
        this->h = h;
        this->lon = lon;
        this->lat = lat;
        isValid = true;
    }

    AreaPoint(
        QString airportId
    ) {
        this->airportId = airportId;
        isValid = false;
    }

    AreaPoint(
            QJsonObject json
    ) {
        this->airportId = json["airportId"].toString();
        this->distance = json["distance"].toDouble();
        this->duration = json["duration"].toDouble();
        this->isValid = json["isValid"].toBool();
        this->w = json["w"].toDouble();
        this->h = json["h"].toDouble();
        this->lon = json["lon"].toDouble();
        this->lat = json["lat"].toDouble();
    }

    AreaPoint() {};

    QJsonObject toJson() override {
        auto json = QJsonObject();
        json["airportId"] = airportId;
        json["distance"] = distance;
        json["duration"] = duration;
        json["isValid"] = isValid;
        json["w"] = w;
        json["h"] = h;
        json["lon"] = lon;
        json["lat"] = lat;
        return json;
    }
};

#endif //AVIA_AREAPOINT_H
