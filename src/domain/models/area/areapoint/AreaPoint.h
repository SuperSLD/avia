//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREAPOINT_H
#define AVIA_AREAPOINT_H

#include <QString>
#include "src/ui/common/navigation/base/basemodel/BaseModel.h"

#include "src/domain/usecases/math/math_functions.h"
using namespace math_functions;

class AreaPoint: public BaseModel {

private:
    void calcS() {
        auto a = distanceInKm(lon, lat, lon + w, lat);
        auto b = distanceInKm(lon, lat, lon, lat + h);
        this->s = a*b;
        this->humanCount = s * p;
    }

public:
    /// ближайший аэропорт
    QString airportId;
    /// расстояние до ближайшего аэропорта
    double distance;
    /// время до ближайшего аэропорта
    /// для средней скорости 60 км/ч
    double duration;
    bool isValid = false;
    double w;
    double h;
    double lon;
    double lat;

    /// площадь
    double s = 0;
    /// плотность населения
    double p = 0;
    /// количество человек
    double humanCount = 0;

    AreaPoint(
        QString airportId,
        double distance,
        double duration,
        double w,
        double h,
        double lon,
        double lat,
        double p = 0
    ) {
        this->airportId = airportId;
        this->distance = distance;
        this->duration = duration;
        this->w = w;
        this->h = h;
        this->lon = lon;
        this->lat = lat;
        this->p = p;
        isValid = true;
        calcS();
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
        this->p = json["p"].toDouble();
        calcS();
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
        json["p"] = p;
        return json;
    }
};

#endif //AVIA_AREAPOINT_H
