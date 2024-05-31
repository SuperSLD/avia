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
    auto timeBars = QList<double>( { original.midTime } );
    auto hubBars = QList<double>( { original.crit(true, original.sumDistance/area.sumArea) } );
    auto maxHub = -299792458299792458.0;
    auto notHubBars = QList<double>( { original.crit(false, original.sumDistance/area.sumArea) } );
    auto maxNotHub = -299792458299792458.0;

    auto greedHubLine = QHash<double, QPair<double, double>>();
    greedHubLine[original.greed] = QPair<double, double>(hubBars.last(), notHubBars.last());
    auto gregariousnessHubLine = QHash<double, QPair<double, double>>();
    gregariousnessHubLine[original.gregariousness] = QPair<double, double>(hubBars.last(), notHubBars.last());

    auto typeBars = QList<double>();
    auto flightBars = QList<double>({ (double) original.allTypesCount });
    auto costBars = QList<double>( { original.cost } );
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
        timeBars.append(graph.midTime);
        hubBars.append(graph.crit(true, plot.last()));
        notHubBars.append(graph.crit(false, plot.last()));

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

            greedHubLine[graph.greed] = QPair<double, double>(hubBars.last(), notHubBars.last());
            gregariousnessHubLine[graph.gregariousness] = QPair<double, double>(hubBars.last(), notHubBars.last());

        saveIndex++;
    }

    for (int i = 0; i < hubBars.size(); i++) {
        auto savedGraph = i == 0 ? original : graphs[i - 1];
        auto saveValues = QList<QString>({
             QString::number(nonStraightness[i], 'f', 4),
             QString::number(plot[i], 'f', 4),
             QString::number(timeBars[i], 'f', 2)
        });
        if (hubBars[i] > maxHub) {
            maxHub = hubBars[i];
            maxHubSave = savedGraph.save;
            maxHubSaveValues = saveValues;
        }
        if (notHubBars[i] > maxNotHub) {
            maxNotHub = notHubBars[i];
            maxNotHubSave = savedGraph.save;
            maxNotHubSaveValues = saveValues;
        }
    }

    nonStraightnessBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            nonStraightness,
            QList<QString>({"Коэффициент непрямолинейности"}),
            QList<double>(),
            saveNames
        )
    );
    plotBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            plot,
            QList<QString>({"Плотность"}),
            QList<double>(),
            saveNames
        )
    );
    timeBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            timeBars,
            QList<QString>({"Доступность"}),
            QList<double>(),
            saveNames
        )
    );
    hubBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            hubBars,
            QList<QString>({"Критериальная функция"}),
            QList<double>(),
            saveNames
        )
    );
    notHubBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            notHubBars,
            QList<QString>({"Критериальная функция"}),
            QList<double>(),
            saveNames
        )
    );

    auto sortedGreedHubKeys = greedHubLine.keys();
    auto sortedGreedHubValues1 = QList<double>();
    auto sortedGreedHubValues2 = QList<double>();
    std::sort(sortedGreedHubKeys.begin(), sortedGreedHubKeys.end());
    foreach(auto key, sortedGreedHubKeys) {
        sortedGreedHubValues1.append(greedHubLine[key].first);
        sortedGreedHubValues2.append(greedHubLine[key].second);
    }
    auto sortedGregariousnessHubKeys = gregariousnessHubLine.keys();
    auto sortedGregariousnessHubValues1 = QList<double>();
    auto sortedGregariousnessHubValues2 = QList<double>();
    std::sort(sortedGregariousnessHubKeys.begin(), sortedGregariousnessHubKeys.end());
    foreach(auto key, sortedGregariousnessHubKeys) {
        sortedGregariousnessHubValues1.append(gregariousnessHubLine[key].first);
        sortedGregariousnessHubValues2.append(gregariousnessHubLine[key].second);
    }

    hubByGreedLineChart.append(
            ChartLine(
                    QList<QString>({colorSecondary()}),
                    sortedGreedHubValues1,
                    QList<QString>({"Хабовая структура"}),
                    sortedGreedHubKeys
            )
    );
    hubByGreedLineChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    sortedGreedHubValues2,
                    QList<QString>({"Не хабовая структура"}),
                    sortedGreedHubKeys
            )
    );
    notHubByGreedLineChart.append(
            ChartLine(
                    QList<QString>({colorSecondary()}),
                    sortedGregariousnessHubValues1,
                    QList<QString>({"Хабовая структура"}),
                    sortedGregariousnessHubKeys
            )
    );
    notHubByGreedLineChart.append(
            ChartLine(
                    QList<QString>({colorPrimary()}),
                    sortedGregariousnessHubValues2,
                    QList<QString>({"Не хабовая структура"}),
                    sortedGregariousnessHubKeys
            )
    );

    auto aircraftModelsBlock = AircraftModelsBlock();
    qDebug() << "MetricsModel количество моделей самолетов" << aircraftModelsBlock.getAircraftCount();
    auto titleRow = QList<QString> { "Самолет", "Дал.", "ВПП", "Скор.", "Крес.", "s0" };
    auto totalRow = QList<QString> { "Всего" , "-", "-", "-", "-", QString::number(original.allTypesCount / 1000) + "K"};
    foreach(auto save, graphs) {
        titleRow.append(save.save);
        totalRow.append(QString::number((int) (save.allTypesCount / save.part / 1000)) + "K");
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

        typeBars.append(typeCount);
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
            saveNames
        )
    );
    typesBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            typeBars,
            QList<QString>({"Количество типов"}),
            QList<double>(),
            saveNames
        )
    );
    flightBarChart.append(
        ChartLine(
            QList<QString> { colorPrimary(), colorSecondary() },
            flightBars,
            QList<QString>({"Количество рейсов"}),
            QList<double>(),
            saveNames
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
            new ChartAnalyticsCell("bar", "Доступность", timeBarChart, true),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("bar", "Хабовая структура", hubBarChart),
            new NumberAnalyticsCell("Сеть " + maxHubSave,"Рациональная сеть для\nхабовой структуры\n\nНепрямолинейность: " + maxHubSaveValues[0] + "\nПлотность: " + maxHubSaveValues[1] + "\nДоступность: " + maxHubSaveValues[2] + " ч", colorPrimary()),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("bar", "Не хабовая структура", notHubBarChart),
            new NumberAnalyticsCell("Сеть " + maxNotHubSave,"Рациональная сеть для\nне хабовой структуры\n\nНепрямолинейность: " + maxNotHubSaveValues[0] + "\nПлотность: " + maxNotHubSaveValues[1] + "\nДоступность: " + maxNotHubSaveValues[2] + " ч", colorPrimary()),
        }))
    );
    rows.append(
        AnalyticsRow(QList<BaseAnalyticsCell *>({
            new ChartAnalyticsCell("line", "Зависимость критерия от жадности", hubByGreedLineChart),
            new ChartAnalyticsCell("line", "Зависимость критерия от стадности", notHubByGreedLineChart),
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
//    rows.append(
//        AnalyticsRow(QList<BaseAnalyticsCell *>({
//                new ChartAnalyticsCell("pie_hide_values", "Распределение типов ВС", optimalTypesPieChart),
//        }))
//    );
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
