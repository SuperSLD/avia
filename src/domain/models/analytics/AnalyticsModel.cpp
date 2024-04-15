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
        }
    }
    airportsCount = airports.values();
    std::sort(airportsCount.begin(), airportsCount.end());
    createDataForCharts();
}

AnalyticsModel::~AnalyticsModel() {

}

void AnalyticsModel::createDataForCharts() {
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
                    QList<QString>({colorSecondary()}),
                    QList<double>({(double) 27.0, 14.0, 40.0, 30.0}),
                    QList<QString>({"Дистанция поменьше"}),
                    QList<double>({(double) 10, 20, 30, 40})
            )
    );

    airportsPieChart.append(
            ChartLine(
                    QList<QString>({colorPrimary(), colorSecondary(), colorBlack()}),
                    QList<double>({(double) airportsCount[airportsCount.size() - 1], (double)  airportsCount[airportsCount.size() - 2], (double) airportsCount[airportsCount.size() - 3]}),
                    QList<QString>({airports.key(airportsCount[airportsCount.size() - 1]), airports.key(airportsCount[airportsCount.size() - 2]), airports.key(airportsCount[airportsCount.size() - 3])})
            )
    );
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
            new NumberAnalyticsCell("#1 " + airports.key(airportsCount[airportsCount.size() - 1]) + "\n#2 " + airports.key(airportsCount[airportsCount.size() - 2]) + "\n#3 " + airports.key(airportsCount[airportsCount.size() - 3]), "Аэропорты с самым большим количеством рейсов", colorPrimary()),
            new ChartAnalyticsCell("pie", "Рейсы крупнейших аэропортов", airportsPieChart),
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
               new ChartAnalyticsCell("line", "Дистанция (хз в чем измененная)", distanceLineChart),
       }))
    );
    return rows;
}