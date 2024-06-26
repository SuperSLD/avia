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
#include "src/domain/usecases/area/atime/ATime.h"
#include "src/domain/usecases/area/taccessibility/TAccessibility.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"

#include <QList>
#include <QJsonArray>

#include <src/ui/theme/AppTheme.h>

#include <cmath> // для round

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
    /// транспортная доступность России
    double taccessibil = 0.0;

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
        taccessibil = json["TAccessibility"].toDouble();
        calcAnalyticsData();
    }

    Area() {}

    void setTAccessibility(double TAccessibility) {
        this->taccessibil = TAccessibility;
    }

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
        json["TAccessibility"] = taccessibil;
        return json;
    }

    QList<AnalyticsRow> getRows(bool isSingle = true) override {
        QList<AnalyticsRow> rows;
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new TitleAnalyticsCell("Результат расчета тр. стандарта"),
            }), true)
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new NumberAnalyticsCell(QString::number(round(taccessibil*100)/100) + " Ч", "Значение транспортного \nстандарта России", colorSecondary()),
            }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                   new NumberAnalyticsCell(QString::number(pointsCount), "Общее количество\nобластей", colorPrimary()),
                   new NumberAnalyticsCell(QString::number((int) maxDistance) + " КМ", "Максимальное расстояние\nдо аэропорта", colorPrimary()),
                   new NumberAnalyticsCell(QString::number((int) maxTime) + " Ч", "Максимальное время\nв пути", colorPrimary()),
            }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                new ChartAnalyticsCell("bar", "Распределение областей", pointsDistancePieChart),
            }))
        );
        rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new ChartAnalyticsCell("bar", "Распределение населения", pointsHumanPieChart),
           }))
        );
        rows.append(
            AnalyticsRow(QList<BaseAnalyticsCell*>({
                new NumberAnalyticsCell(QString::number((int) (pointsHumans[0] / 1000)) + " К\nчеловек", "В самой близкой области\nдоступности " + QString::number((int) (maxTime / colors.size())) + "ч находится " + QString::number((int)(pointsHumans[0]*100/pointsHumansSum)) + "% населения", colors[0]),
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

    double calcTime(TransportGraphModel graph) {
        double TAcces;
        QList<ATime> atime;
        QList<TAccessibility> tAcc;

        for (int i =0; i < graph.airports.size(); i++)
        {
            double humans =0;
            double averageTime =0;
            int count = 0;
            for (int j =0; j < points.size(); j++)
            {
                for (int k=0; k < points.at(j).size(); k++)
                {
                    if (points[j][k].airportId == graph.airports[i].id)
                    {
                        humans = humans + points[j][k].humanCount;
                        count ++;
                    }
                }
            }
            for (int j =0; j < points.size(); j++)
            {
                for (int k=0; k < points.at(j).size(); k++)
                {
                    if (points[j][k].airportId == graph.airports[i].id)
                    {
                        averageTime = averageTime + (points[j][k].humanCount / humans * points[j][k].duration);
                    }
                }
            }
            atime.append(ATime(graph.airports[i].id, averageTime, count));
        }
        //
        qDebug() << "Количество пассажиров - " << graph.passCount;
        qint64 totalPass = graph.passCount;
        double avTime = 0.0; // среднее время

        for (int i=0; i < points.size(); i++) {
            for (int j =0; j < points.at(i).size(); j++) {
                double dur1 = 0; // длительность поездки на автомобиле в зоне конечного аэропорта
                double dur2 = 0.0; // длительность перелета из начального аэропорта в конечный
                double dur3 = 0.0; // длительность поездки на автомобиле в зоне начального аэропорта
                int indIn = 0; // индекс конечного аэропорта
                int indOut = 0; // индекс начального аэропорта
                for (int u=0; u < graph.airports.size(); u++) {
                    if (graph.airports.at(u).id == points.at(i).at(j).airportId) indIn = u;
                }
                dur1 = atime[indIn].aTime;
                for (int y=0; y < graph.airports.at(indIn).connectedAirports.size(); y++) {
                    double distanceOfFly = 0.0; // дистанция перелета
                    double PassFromTo = 0; // пассажиропотоке на конкретном перелете
                    for (int b = 0; b < graph.airports.size(); b++) {
                        if (graph.airports[indIn].connectedAirports.at(y) == graph.airports[b].id) {
                            indOut = b;
                            dur3 = atime[indOut].aTime;
                            distanceOfFly = distanceInKm(graph.airports.at(indIn).lon, graph.airports.at(indIn).lat, graph.airports.at(indOut).lon, graph.airports.at(indOut).lat);
                            double speed;
                            for (int f=0; f < graph.airports[indIn].connectedAircraft.size(); f ++)
                            {
                                speed = graph.airports[indIn].connectedAircraft.value(graph.airports[indOut].id).speed;
                            }
                            //qDebug() << "скорость самолета - " << speed;
                            if (speed > 1)
                            {
                                dur2 = distanceOfFly / speed;
                            }
                            else
                            {
                                dur2 = distanceOfFly / 650;
                            }
                            PassFromTo = graph.airports.at(indIn).connectedPassCount.value(graph.airports.at(indOut).id);
                            avTime = avTime + (dur1 + dur2 + dur3)*(PassFromTo/totalPass)/atime[indIn].count;
                            //for (int f = 0; f < points.size(); f++) {
                              //  for (int g = 0; g < points.at(f).size(); g++) {
                                //    if (points.at(f).at(g).airportId == graph.airports.at(indOut).id) {
                                  //      avTime = avTime + (dur1 + dur2 + dur3)*(PassFromTo/totalPass);
                                    //}
                                //}
                            //}
                        }
                    }
                }
                //tAcc.append(TAccessibility(points.at(i).at(j).lon, points.at(i).at(j).lat, averageTime));
            }
        }
        //double summm= 0.0;
        //int kolichestvo = 0;
        //for (int tt =0; tt < tAcc.size(); tt++) {
            //if (tAcc.at(tt).tAccessibility != std::numeric_limits<double>::infinity()) {
                //summm = summm + tAcc[tt].tAccessibility;
                //kolichestvo ++;
            //}
        //}
        //TAcces = summm / kolichestvo;
        TAcces = avTime;
        qDebug() << "Количество человек в самой близкой области" << (pointsHumans[0] / 1000);
        return TAcces;
    }
};

#endif //AVIA_AREA_H
