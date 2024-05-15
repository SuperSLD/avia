//
// Created by Леонид Соляной on 13.05.2024.
//

#include "MetricsModel.h"
#include "src/domain/models/transportgraph/aircraftmodels/AircraftModelsBlock.h"
#include "src/domain/models/analytics/view/TableAnalyticsCell.h"

MetricsModel::MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area) {
    auto nonStraightness = QList<double> { original.nonStraightness };
    auto saveNames = QList<QString> { original.save };
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

    auto aircraftModelsBlock = AircraftModelsBlock();
    auto titleRow = QList<QString> { "Самолет", "Дальность", "Скорость", "Кресел", "s0" };
    auto totalRow = QList<QString> { "Всего" , "-", "-", "-", QString::number(original.allTypesCount * 0.001)};
    foreach(auto save, graphs) {
        titleRow.append(save.save);
        totalRow.append(QString::number(save.allTypesCount));
    }
    aircraftModelsTable.append(titleRow);
    aircraftModelsTable.append(totalRow);
    foreach(auto key, original.aircraftCount.keys()) {
        auto row = QList<QString>();
        auto rowAircraft = aircraftModelsBlock.getByModel(key);
        if (rowAircraft.use) {
            row.append(rowAircraft.modelName);
            row.append(QString::number(rowAircraft.range) + " км");
            row.append(QString::number(rowAircraft.speed) + " км/ч");
            row.append(QString::number(rowAircraft.seatsCount));
            row.append(QString::number((original.aircraftCount[key] * 100 / (double) original.allTypesCount), 'f', 1) + "%");
            foreach(auto save, graphs) {
                if (save.aircraftCount.contains(key)) {
                    row.append(QString::number(save.aircraftCount[key] * 100 / (double) save.allTypesCount, 'f', 1) + "%");
                } else {
                    row.append("---");
                }
            }
            aircraftModelsTable.append(row);
        }
    }
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
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TableAnalyticsCell(aircraftModelsTable, true),
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
