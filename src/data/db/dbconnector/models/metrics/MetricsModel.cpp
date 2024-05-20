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


    auto allGraphs = QList<TransportGraphModel> {original};
    foreach (auto graph, graphs) {
        allGraphs.append(graph);
    }
    titleRow = QList<QString> {""};
    auto typeRow = QList<QString> {"Количество типов"};
    auto costRow = QList<QString> {"Стоимость перевозок"};
    auto countRow = QList<QString> {"Количество самолетов"};
    auto partRow = QList<QString> {"Расчетная часть пассажиров"};
    foreach(auto graph, allGraphs) {
        auto typeCount = 0;
        foreach(auto type, graph.aircraftCount.values()) {
            if (type * 100 / (double) graph.allTypesCount >= 0.1) typeCount++;
        }
        titleRow.append(graph.save);
        typeRow.append(QString::number(typeCount));
        costRow.append(QString::number((graph.cost / graph.part) / (double) 1000000, 'f', 2) + "M");
        countRow.append(QString::number((int) (graph.allTypesCount / graph.part) / 1000) + "K");
        partRow.append(QString::number(graph.part * 100, 'f', 2) + "%");
    }
    parkDiffTable.append(titleRow);
    parkDiffTable.append(typeRow);
    parkDiffTable.append(costRow);
    parkDiffTable.append(countRow);
    parkDiffTable.append(partRow);
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
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TableAnalyticsCell(parkDiffTable, true),
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
