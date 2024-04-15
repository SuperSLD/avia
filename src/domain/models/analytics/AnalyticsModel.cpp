//
// Created by Леонид Соляной on 10.04.2024.
//

#include "AnalyticsModel.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"
#include "src/domain/models/analytics/view/chart/ChartAnalyticsCell.h"
#include <QList>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

AnalyticsModel::AnalyticsModel(QList<FlightModel *> flights) {
    allCount = flights.size();
    foreach(auto flight, flights) {
        //distance.append(50.0);//flight->data.distance.toDouble());
        //distance2.append(40.0);//flight->data.distance.toDouble() * 0.7);
        distance.append(flight->data.distance.toDouble());
        distance2.append(flight->data.distance.toDouble() * 0.7);
        if (flight->data.apdstco == "Russia" && flight->data.aporgco == "Russia") {
            inRussiaCount++;
        } else {
            notRussia++;
        }
    }
    flightCountPieChart.append(
        ChartLine(
                QList<QString>({colorPrimary(), colorSecondary()}),
                QList<double>({(double) inRussiaCount, (double)  notRussia}),
                QList<QString>({"В россии", "За границу"})
        )
    );

    flightCountBarChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia}),
                    QList<QString>({"В россии и за границей"}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia})
            )
    );

//    distanceLineChart.append(
//            ChartLine(
//                    QList<QString>({colorPrimary()}),
//                    distance,
//                    QList<QString>({"Дистанция"}),
//                    distance
//            )
//    );
//    distanceLineChart.append(
//            ChartLine(
//                    QList<QString>({colorSecondary()}),
//                    distance2,
//                    QList<QString>({"Дистанция поменьше"}),
//                    distance2
//            )
//    );
    distanceLineChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    QList<double>({(double) 20.0, 24.0, 10.0, 54.0, 40.0}),
                    QList<QString>({"Дистанция"}),
                    QList<double>({(double) 10, 20, 30, 40, 50})
            )
    );
    distanceLineChart.append(
            ChartLine(
                    QList<QString>({colorRed()}),
                    QList<double>({(double) 0.0, 10.0, 20.0, 30.0, 54.0}),
                    QList<QString>({"Дистанция"}),
                    QList<double>({(double) 10, 20, 30, 40, 50})
            )
    );
    distanceLineChart.append(
            ChartLine(
                    QList<QString>({colorSecondary()}),
                    QList<double>({(double) 27.0, 14.0, 40.0, 30.0}),
                    QList<QString>({"Дистанция поменьше"}),
                    QList<double>({(double) 10, 20, 30, 40})
            )
    );
}

AnalyticsModel::~AnalyticsModel() {

}

QList<AnalyticsRow> AnalyticsModel::getRows() {
    QList<AnalyticsRow> rows;
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
            new TitleAnalyticsCell("Общие данные"),
        }), true)
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
            new NumberAnalyticsCell(QString::number(allCount), "Общее количество\nперелетов", colorPrimary()),
            new NumberAnalyticsCell(QString::number(inRussiaCount), "Общее количество перелетов внутри страны", colorPrimary()),
            new NumberAnalyticsCell(QString::number(notRussia), "Количество перелетов с одним аэропортом в России", colorSecondary()),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new ChartAnalyticsCell("bar", "Распределение рейсов", flightCountBarChart),
           new ChartAnalyticsCell("pie", "Распределение рейсов", flightCountPieChart),
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new ChartAnalyticsCell("line", "Дистанция (хз в чем измененная)", distanceLineChart),
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new ChartAnalyticsCell("line", "Дистанция (хз в чем измененная)", distanceLineChart),
           new ChartAnalyticsCell("line", "Дистанция (хз в чем измененная)", distanceLineChart),
        }))
    );
    return rows;
}
