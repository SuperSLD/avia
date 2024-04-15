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
                    QList<QString>({colorSecondary()}),
                    QList<double>({(double) allCount, (double)  allCount}),
                    QList<QString>({"Все рейсы"}),
                    QList<double>({(double) allCount, (double)  allCount})
            )
    );
    flightCountBarChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia, 30000.0, 13000.0, 13000.0, 13000.0}),
                    QList<QString>({"В россии и за границей"}),
                    QList<double>({(double) inRussiaCount, (double)  notRussia, 30000.0, 13000.0, 13000.0, 13000.0})
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
       }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell*>({
           new ChartAnalyticsCell("bar", "Распределение рейсов", flightCountBarChart),
           new ChartAnalyticsCell("pie", "Распределение рейсов", flightCountPieChart),
       }))
    );
    return rows;
}
