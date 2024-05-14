//
// Created by Леонид Соляной on 13.05.2024.
//

#include "MetricsModel.h"

MetricsModel::MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area) {
    auto saveNames = QList<QString> { original.save };
    auto nonStraightness = QList<double> { original.nonStraightness };
    foreach(auto graph, graphs) {
        saveNames.append(graph.save);
        nonStraightness.append(graph.nonStraightness);
    }

    nonStraightnessBarChart.append(
        ChartLine(
            QList<QString>({colorPrimary()}),
            nonStraightness,
            QList<QString>({"коэффициент непрямолинейности"}),
            QList<double>(),
            saveNames
        )
    );
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
            new ChartAnalyticsCell("bar", "Коэффициент непрямолинейности", nonStraightnessBarChart),
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
