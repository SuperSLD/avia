//
// Created by Леонид Соляной on 10.04.2024.
//

#include "AnalyticsModel.h"
#include "src/domain/models/analytics/view/TitleAnalyticsCell.h"
#include <QList>

AnalyticsModel::AnalyticsModel(QList<FlightModel *> flights) {
    allCount = flights.size();
    foreach(auto flight, flights) {
        if (flight->data.apdstco == "Russia" && flight->data.aporgco == "Russia") {
            inRussiaCount++;
        } else {
            notRussia++;
        }
    }
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
            new NumberAnalyticsCell(QString::number(allCount), "Общее количество\nперелетов", colorSecondary()),
            new NumberAnalyticsCell(QString::number(inRussiaCount), "Общее количество перелетов внутри страны", colorPrimary()),
            new NumberAnalyticsCell(QString::number(notRussia), "Количество перелетов с одним аэропортом в России", colorPrimary()),
        }))
    );
    return rows;
}
