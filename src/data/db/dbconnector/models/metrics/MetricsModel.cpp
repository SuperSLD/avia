//
// Created by Леонид Соляной on 13.05.2024.
//

#include "MetricsModel.h"

MetricsModel::MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area) {

}

QList<AnalyticsRow> MetricsModel::getRows(bool isSingle) {
    QList<AnalyticsRow> rows;
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TitleAnalyticsCell("Итоги анализа транспортных сетей"),
        }), true)
    );
    rows.append(
         AnalyticsRow(QList<BaseAnalyticsCell *>({
            new NumberAnalyticsCell("Тут будут результаты вычислений","Но пока их нет", colorSecondary()),
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
