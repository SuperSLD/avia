//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREA_H
#define AVIA_AREA_H

#include "src/domain/models/analytics/BaseAnalyticModel.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"

#include <QList>
#include <QJsonArray>

class Area: public BaseAnalyticModel {

private:
    void calcAnalyticsData() {

    }

public:
    QList<QList<AreaPoint>> points;
    double maxDistance = 0;
    double maxTime = 0;

    Area(QList<QList<AreaPoint>> points) {
        this->points = points;
        foreach(auto line, points) {
            foreach(auto point, line) {
                if (point.distance > maxDistance) {
                    maxDistance = point.distance;
                }
                if (point.duration > maxTime) {
                    maxTime = point.duration;
                }
            }
        }
        calcAnalyticsData();
    }

    Area(QJsonObject json) {
        foreach(auto line, json["points"].toArray()) {
            QList<AreaPoint> arr;
            foreach(auto point, line.toArray()) {
                auto areaPoint = AreaPoint(point.toObject());
                arr.append(areaPoint);
                if (areaPoint.distance > maxDistance) {
                    maxDistance = areaPoint.distance;
                }
                if (areaPoint.duration > maxTime) {
                    maxTime = areaPoint.duration;
                }
            }
            points.append(arr);
        }
        calcAnalyticsData();
    }

    Area() {}

    QJsonObject toJson() override {
        auto json = QJsonObject();
        auto arr = QJsonArray();
        foreach(auto line, points) {
            auto lonArr = QJsonArray();
            foreach(auto point, line) {
                lonArr.append(point.toJson());
            }
            arr.append(lonArr);
        }
        json["points"] = arr;
        return json;
    }

    QList<AnalyticsRow> getRows() override {
        QList<AnalyticsRow> rows;
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new TitleAnalyticsCell("Результаты вычислений"),
            }), true)
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new NumberAnalyticsCell(QString::number(points.size()), "Общее количество\nсекторов", colorSecondary()),
                   new NumberAnalyticsCell(QString::number((int) maxDistance) + " КМ", "Максимальное расстояние\nдо аэропорта", colorPrimary()),
                   new NumberAnalyticsCell(QString::number((int) maxTime) + " Ч", "Максимальере время\nв пути", colorPrimary()),
            }))
        );
        return rows;
    }
};

#endif //AVIA_AREA_H
