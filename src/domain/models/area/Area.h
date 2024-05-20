//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_AREA_H
#define AVIA_AREA_H

#include "src/domain/models/analytics/BaseAnalyticModel.h"
#include "src/domain/models/area/areapoint/AreaPoint.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"
#include "src/domain/models/analytics/view/chart/ChartAnalyticsCell.h"
#include "src/domain/models/analytics/view/EmpyAnalyticsCell.h"

#include <QList>
#include <QJsonArray>

#include <src/ui/theme/AppTheme.h>

using namespace theme;

class Area: public BaseAnalyticModel {

private:
    void calcAnalyticsData() {
        for(int i = 0; i < colors.size(); i++) {
            pointsDistance.append(0.0);
            pointsHumans.append(0.0);
        }
        foreach(auto line, points) {
            foreach(auto point, line) {
                pointsCount++;
                auto colorIndex = (int) (point.distance / (double) maxDistance * (colors.size() - 1));
                pointsDistance[colorIndex] += 1.0;
                pointDistanceSum += 1.0;
                pointsHumans[colorIndex] += point.humanCount;
                pointsHumansSum += point.humanCount;
                if (pointsDistance[colorIndex] > maxDistanceCount) {
                    maxDistanceCount = pointsDistance[colorIndex];
                    maxDistanceCountZone = colorIndex;
                }
                sumArea += point.s;
            }
        }

        QList<QString> pointsDistanceNames;
        for (int i = 0; i < colors.size(); i++) {
            pointsDistanceNames.append(
                    QString::number((int) (maxTime / colors.size() * (1 + i))) + "ч"
            );
        }
        pointsDistancePieChart.append(
            ChartLine(
                    colors,
                    pointsDistance,
                    QList<QString>({"Количество секторов"}),
                    QList<double>(),
                    pointsDistanceNames
            )
        );
        pointsHumanPieChart.append(
            ChartLine(
                    colors,
                    pointsHumans,
                    QList<QString>({"Количество человек"}),
                    QList<double>(),
                    pointsDistanceNames
            )
        );
    }

    int maxDistanceCount = 0;
    int maxDistanceCountZone = 0;
    QList<double> pointsDistance;
    int pointDistanceSum = 0;
    QList<double> pointsHumans;
    double pointsHumansSum;
    QList<ChartLine> pointsDistancePieChart;
    QList<ChartLine> pointsHumanPieChart;

public:
    QList<QList<AreaPoint>> points;

    /// максимальное расстояние до аэропорта
    double maxDistance = 0;
    /// максимальное время до аэропорта
    double maxTime = 0;
    /// количество точек
    int pointsCount = 0;
    /// суммарная площадь секторов
    double sumArea = 0.0;

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

    QList<AnalyticsRow> getRows(bool isSingle = true) override {
        QList<AnalyticsRow> rows;
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new TitleAnalyticsCell("Результат расчета зон тр. дост."),
            }), true)
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new NumberAnalyticsCell(QString::number(pointsCount), "Общее количество\nсекторов", colorSecondary()),
                   new NumberAnalyticsCell(QString::number((int) maxDistance) + " КМ", "Максимальное расстояние\nдо аэропорта", colorPrimary()),
                   new NumberAnalyticsCell(QString::number((int) maxTime) + " Ч", "Максимальере время\nв пути", colorPrimary()),
            }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                new ChartAnalyticsCell("bar", "Распределение зон", pointsDistancePieChart),
            }))
        );
        rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new ChartAnalyticsCell("bar", "Распределение зон", pointsHumanPieChart),
           }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                new NumberAnalyticsCell(QString::number((int) (pointsHumans[0] / 1000)) + " К\nчеловеек", "В самой близкой зоне\nдоступности " + QString::number((int) (maxTime / colors.size())) + "ч находится " + QString::number((int)(pointsHumans[0]*100/pointsHumansSum)) + "% населения", colors[0]),
                //new NumberAnalyticsCell(QString::number((int) (maxDistanceCount / 1000)) + " К\nчеловек", "Самая частая зона\nдоступности " + QString::number((int) (maxTime / colors.size() * (1 + maxDistanceCountZone))) + "ч составляет " + QString::number((int)(pointsDistance[maxDistanceCountZone]*100/pointDistanceSum)) + "% населения", colors[maxDistanceCountZone]),
            }))
        );
        if (isSingle) {
            rows.append(
                AnalyticsRow(QList<BaseAnalyticsCell*>({
                       new EmptyAnalyticsCell(),
               }), true)
            );
        }
        return rows;
    }
};

#endif //AVIA_AREA_H
