//
// Created by Леонид Соляной on 13.05.2024.
//

#include "MetricsModel.h"
#include "src/domain/models/transportgraph/aircraftmodels/AircraftModelsBlock.h"
#include "src/domain/models/analytics/view/TableAnalyticsCell.h"

MetricsModel::MetricsModel(TransportGraphModel original, QList<TransportGraphModel> graphs, Area area) {
    auto nonStraightness = QList<double> { original.nonStraightness };
    auto saveNames = QList<QString> { original.save };
    auto saveNamesNotFull = QList<QString>();
    auto plot = QList<double> { original.sumDistance / area.sumArea };

    auto typeBars = QList<double>();
    auto flightBars = QList<double>();
    auto costBars = QList<double>();
    auto minCost = 299792458299792458.0;
    auto minCostSaveIndex = -1;

    auto greedLine = QHash<double, double>();
    auto gregariousnessLine = QHash<double, double>();
    auto greedByCost = QHash<double, QPair<double, double>>();

    auto saveIndex = 0;
    foreach(auto graph, graphs) {
        saveNames.append(graph.save);
        saveNamesNotFull.append(graph.save);
        nonStraightness.append(graph.nonStraightness);
        plot.append(graph.sumDistance / area.sumArea);

        // данные для графиков анализа парков
        flightBars.append(graph.allTypesCount);
        costBars.append(graph.cost);
        if (graph.cost < minCost) {
            minCost = graph.cost;
            minCostSaveIndex = saveIndex;
            optimalSave = graph.save;
        }

        greedLine[graph.greed] = graph.cost;
        gregariousnessLine[graph.gregariousness] = graph.cost;
        greedByCost[graph.cost] = QPair<double, double>(graph.greed, graph.gregariousness);

        saveIndex++;
    }

    nonStraightnessBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            nonStraightness,
            QList<QString>({"коэффициент непрямолинейности"}),
            QList<double>(),
            saveNames
        )
    );
    plotBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            plot,
            QList<QString>({"плотность"}),
            QList<double>(),
            saveNames
        )
    );

    auto aircraftModelsBlock = AircraftModelsBlock();
    qDebug() << "MetricsModel количество моделей самолетов" << aircraftModelsBlock.getAircraftCount();
    auto titleRow = QList<QString> { "Самолет", "Дал.", "ВПП", "Скор.", "Крес.", "s0" };
    auto totalRow = QList<QString> { "Всего" , "-", "-", "-", "-", QString::number(original.allTypesCount / 1000) + "K"};
    foreach(auto save, graphs) {
        titleRow.append(save.save);
        totalRow.append(QString::number(save.allTypesCount / save.part / 1000) + "K");
    }
    aircraftModelsTable.append(titleRow);
    aircraftModelsTable.append(totalRow);
    foreach(auto key, aircraftModelsBlock.getKeys()) {
        auto row = QList<QString>();
        auto rowAircraft = aircraftModelsBlock.getByModel(key);
        if (rowAircraft.use) {
            row.append(rowAircraft.modelName);
            row.append(QString::number(rowAircraft.range) + " км");
            row.append(QString::number(rowAircraft.vppLen) + " м");
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
    auto countRow = QList<QString> {"Количество рейсов"};
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

        if (graph.save != "s0") {
            typeBars.append(typeCount);
        }
    }
    parkDiffTable.append(titleRow);
    parkDiffTable.append(typeRow);
    parkDiffTable.append(costRow);
    parkDiffTable.append(countRow);
    parkDiffTable.append(partRow);

    costBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            costBars,
            QList<QString>({"Стоимость рейсов"}),
            QList<double>(),
            saveNamesNotFull
        )
    );
    typesBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            typeBars,
            QList<QString>({"Количество типов"}),
            QList<double>(),
            saveNamesNotFull
        )
    );
    flightBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            flightBars,
            QList<QString>({"Количество рейсов"}),
            QList<double>(),
            saveNamesNotFull
        )
    );

    auto sortedGreedKeys = greedLine.keys();
    auto sortedGreedValues = QList<double>();
    std::sort(sortedGreedKeys.begin(), sortedGreedKeys.end());
    foreach(auto key, sortedGreedKeys) {
        sortedGreedValues.append(greedLine[key]);
    }
    auto sortedGregariousnessKeys = gregariousnessLine.keys();
    auto sortedGregariousnessValues = QList<double>();
    std::sort(sortedGregariousnessKeys.begin(), sortedGregariousnessKeys.end());
    foreach(auto key, sortedGregariousnessKeys) {
        sortedGregariousnessValues.append(gregariousnessLine[key]);
    }

    auto sortedGreedByCostKeys = greedByCost.keys();
    auto greedByCostValues = QList<double>();
    auto gregariousnessByCostValues = QList<double>();
    std::sort(sortedGreedByCostKeys.begin(), sortedGreedByCostKeys.end());
    foreach(auto key, sortedGreedByCostKeys) {
        greedByCostValues.append(greedByCost[key].first);
        gregariousnessByCostValues.append(greedByCost[key].second);
    }

    costLineChart.append(
        ChartLine(
            QList<QString>({colorSecondary()}),
            sortedGreedValues,
            QList<QString>({"Стоимость от жадности"}),
            sortedGreedKeys
        )
    );
    costLineChart.append(
        ChartLine(
            QList<QString>({colorPrimary()}),
            sortedGregariousnessValues,
            QList<QString>({"Стоимость от стадности"}),
            sortedGregariousnessKeys
        )
    );

    greedLineChart.append(
        ChartLine(
            QList<QString>({colorSecondary()}),
            greedByCostValues,
            QList<QString>({"Жадность от стоимости"}),
            sortedGreedByCostKeys
        )
    );
    gregariousnessLineChart.append(
        ChartLine(
            QList<QString>({colorPrimary()}),
            gregariousnessByCostValues,
            QList<QString>({"Стадность от стоимости"}),
            sortedGreedByCostKeys
        )
    );

    optimalParkTable.append(QList<QString>{ "Модель", "Код", "Скорость", "Кресел", "ВПП", "Дальность", "Количество" });
    auto optimalTypes = QList<double>();
    auto optimalTypesKeys = QList<QString>();
    foreach(auto key, graphs[minCostSaveIndex].aircraftCount.keys()) {
        auto aircraft = aircraftModelsBlock.getByModel(key);
        optimalParkTable.append(
            QList<QString> {
                aircraft.modelName,
                aircraft.model,
                QString::number(aircraft.speed) + " км/ч",
                QString::number(aircraft.seatsCount),
                QString::number(aircraft.vppLen) + " м",
                QString::number(aircraft.range) + " км",
                QString::number(graphs[minCostSaveIndex].aircraftCount[key] * 100 / (double) graphs[minCostSaveIndex].allTypesCount, 'f', 1) + "%"
            }
        );
        optimalTypes.append(graphs[minCostSaveIndex].aircraftCount[key] * 100 / (double) graphs[minCostSaveIndex].allTypesCount);
        optimalTypesKeys.append(key);
    }

    optimalTypesPieChart.append(
            ChartLine(
                    QList<QString>({ colors }),
                    optimalTypes,
                    optimalTypesKeys
            )
    );

    qDebug() << sortedGregariousnessKeys;
    qDebug() << sortedGregariousnessValues;
    qDebug() << sortedGreedKeys;
    qDebug() << sortedGreedValues;
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
            new TitleAnalyticsCell("Результаты сравнения графов", true),
        }), true)
    );
    rows.append(
         AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("bar", "Коэффициент непрямолинейности", nonStraightnessBarChart),
            new ChartAnalyticsCell("bar", "Плотность", plotBarChart),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TitleAnalyticsCell("Таблица используемых ВС (используемые ВС указаны в процентах от общего количества)", true),
        }), true)
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TableAnalyticsCell(aircraftModelsTable, true),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TitleAnalyticsCell("Сравнение полученных парков ВС", true),
        }), true)
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TableAnalyticsCell(parkDiffTable, true),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("bar", "Количество типов", typesBarChart, true),
            new ChartAnalyticsCell("bar", "Количество рейсов", flightBarChart, true),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("bar", "Стоимость рейсов", costBarChart, true),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("line", "Зависимость стоимости от жадности и стадности", costLineChart),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("line", "Жадность от стоимости", greedLineChart),
            new ChartAnalyticsCell("line", "Стадность от стоимости", gregariousnessLineChart),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TitleAnalyticsCell("Оптимальным парком по стоимости является " + optimalSave + "\nНиже приведена информация о нем.", true),
        }), true)
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
                new ChartAnalyticsCell("pie", "Распределение типов ВС", optimalTypesPieChart),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new TableAnalyticsCell(optimalParkTable, true),
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
