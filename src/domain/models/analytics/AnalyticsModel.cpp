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
        if (flight->data.apdstco == "Russia" && flight->data.aporgco == "Russia") {
            inRussiaCount++;
            airports[flight->data.apdstia] += 1;
        } else {
            notRussia++;
            airportsOut[flight->data.apdstia] += 1;
        }
    }
    airportsCount = airports.values();
    std::sort(airportsCount.begin(), airportsCount.end());
    airportsCountOut = airportsOut.values();
    std::sort(airportsCountOut.begin(), airportsCountOut.end());
    createDataForCharts();
}

AnalyticsModel::~AnalyticsModel() {

}

void AnalyticsModel::createDataForCharts() {
    flightCountBarChart.append(
            ChartLine(
                    QList<QString>({colorPrimary(), colorSecondary()}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia}),
                    QList<QString>({"В россии и за границей"}),
                    QList<double>(),
                    QList<QString>({"Внутренние", "Внешние"})
            )
    );

    flightCountPieChart.append(
            ChartLine(
                    QList<QString>({colorPrimary(), colorSecondary()}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia}),
                    QList<QString>({"В россии", "За границу"})
            )
    );

    distanceLineChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    QList<double>({(double) 200.0, 240.0, 100.0, 540.0, 400.0}),
                    QList<QString>({"Дистанция"}),
                    QList<double>({(double) 10, 20, 30, 40, 50})
            )
    );
    distanceLineChart.append(
            ChartLine(
                    QList<QString>({colorSecondary()}),
                    QList<double>({(double) 270.0, 140.0, 400.0, 300.0}),
                    QList<QString>({"Дистанция поменьше"}),
                    QList<double>({(double) 10, 20, 30, 40})
            )
    );

    sumOfTopAirports = airportsCount[airportsCount.size() - 1] + airportsCount[airportsCount.size() - 2] + airportsCount[airportsCount.size() - 3];
    percentOfTopAirports = sumOfTopAirports / (double) inRussiaCount * 100;
    airportsPieChart.append(
            ChartLine(
                    QList<QString>({colorPrimary(), colorSecondary(), colorBlack()}),
                    QList<double>({(double) airportsCount[airportsCount.size() - 1], (double)  airportsCount[airportsCount.size() - 2], (double) airportsCount[airportsCount.size() - 3]}),
                    QList<QString>({airports.key(airportsCount[airportsCount.size() - 1]), airports.key(airportsCount[airportsCount.size() - 2]), airports.key(airportsCount[airportsCount.size() - 3])})
            )
    );

    QList<QString> airportCountName;
    QList<double> airportCountValue;
    for (int i = 0; i < 13; i++) {
        airportCountName.append(airports.key(airportsCount[airportsCount.size() - 1 - i]));
        airportCountValue.append(airportsCount[airportsCount.size() - 1 - i]);
    }
    QList<double> airportCountValueOut;
    for (int i = 0; i < 13; i++) {
        airportCountValueOut.append(airportsCountOut[airportsCountOut.size() - 1 - i]);
    }
    airportsBarChart.append(
            ChartLine(
                    QList<QString>({colorSecondary()}),
                    airportCountValue,
                    QList<QString>({"Внутренние рейсы"}),
                    QList<double>(),
                    airportCountName
            )
    );
    airportsBarChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    airportCountValueOut,
                    QList<QString>({"Внешние рейсы"})
            )
    );
}


QList<AnalyticsRow> AnalyticsModel::getRows(bool isSingle) {
    QList<AnalyticsRow> rows;
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
            new TitleAnalyticsCell("Общие данные о рейсах"),
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
            new ChartAnalyticsCell("pie", "Рейсы крупнейших аэропортов", airportsPieChart),
            new NumberAnalyticsCell(
                    "#1 " + airports.key(airportsCount[airportsCount.size() - 1]) + "\n#2 " + airports.key(airportsCount[airportsCount.size() - 2]) + "\n#3 " + airports.key(airportsCount[airportsCount.size() - 3]),
                    "Аэропорты с самым большим количеством рейсов принимают на себя " + QString::number(sumOfTopAirports) + " перелетов, что составляет " + QString::number(percentOfTopAirports) + "% от общего количества внутренних перелетов",
                    colorPrimary()
            ),
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new ChartAnalyticsCell("bar", "Распределение рейсов по аэропортам", airportsBarChart),
       }))
    );
//    rows.append(
//        AnalyticsRow(QList<BaseAnalyticsCell*>({
//               new ChartAnalyticsCell("line", "Проверка графика (случайные цифры)", distanceLineChart),
//       }))
//    );
    return rows;
}