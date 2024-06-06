//
// Created by Леонид Соляной on 03.06.2024.
//

#include "NewAirportsWorker.h"
#include "src/domain/models/area/Area.h"
#include "src/domain/usecases/graph/AntOptimisation.h"
#include "src/domain/usecases/area/CalcNewArea.h"


void NewAirportsWorker::run() {
    qDebug() << "NewAirportsWorker начал считать";

    /// тут считашь
    /// 1
    newAirports.append(AirportModel("USDA", "Sabetta", "Sabetta", 66.92089, 71.23811, 10498, 11289, {}));
    /// 2
    newAirports.append(AirportModel("UHMB", "Baranikha", "Bilibino", 168.25738, 68.49535, 1714, 2557, {}));
    /// 3
    newAirports.append(AirportModel("USDM", "Utrenniy", "Utrenniy", 74.25971, 71.01116, 2557, 14604, {}));
    /// 4
    newAirports.append(AirportModel("UESS", "Cherskyi", "Cherskyi", 161.33972, 68.74128, 19167, 12785, {}));
    /// 5
    newAirports.append(AirportModel("UODD", "Dikson", "Dikson", 80.37941, 73.51784, 2843, 2191, {}));
    /// 6
    newAirports.append(AirportModel("UESA", "Andryushkino", "Andryushkino", 154.4608, 69.17023, 11289, 25570, {}));
    /// 7
    newAirports.append(AirportModel("UODL", "Mys Chelyuskin", "Mys Chelyuskin", 104.71370, 77.71370, 2377, 3284, {}));
    /// 8
    newAirports.append(AirportModel("UEBE", "Tenkeli", "Deputatskiy", 140.70743, 70.16503, 3284, 2377, {}));
    /// 9
    newAirports.append(AirportModel("UOHH", "Khatanga", "Khatanga", 102.49318, 71.9784, 25570, 11289, {}));
    /// 10
    newAirports.append(AirportModel("UEBK", "Kular", "Kazachie", 134.50997, 70.59633, 2191, 2843, {}));
    /// 11
    newAirports.append(AirportModel("UOHK", "Mys Kosistiy", "Mys Kosistiy", 109.75975, 73.66215, 12785, 19167, {}));
    /// 12
    newAirports.append(AirportModel("UESB", "Bulun", "Kusur", 127.3955, 70.69823, 1825, 2557, {}));
    /// 13
    newAirports.append(AirportModel("UERB", "Anabar", "Ebelyah", 113.5808, 70.88308, 14604, 1714, {}));
    /// 14
    newAirports.append(AirportModel("UETT", "Taymylyr", "Taymylyr", 121.8716, 72.62633, 11289, 10498, {}));

    graph.airports.append(newAirports[0]);

    /// посчитанные зоны доступности
    //auto area = Area(settingsRepository->getJson("area"));

    /// пример того как пользоваться муравьиным алгоритмом
    auto *aco = new AntColonyOptimization(
            "s5",
            graph.airports,
            1, // жадность выберешь сам
            1, // стадность выберешь сам
            1.0
    );

    auto newGraph = aco->distributePassengers();
    auto calcArea = CalcNewArea();
    auto points = calcArea.calcPoints(newGraph);

    emit onChangeProgress(1);

    auto area = Area(points);
    area.setTAccessibility(area.calcTime(newGraph));

    for (int i=1; i < newAirports.size(); i++)
    {
        graph.airports.append(newAirports[i]);
        emit onChangeProgress(i+1);
        auto *ac = new AntColonyOptimization(
            "s5",
            graph.airports,
            1, // жадность выберешь сам
            1, // стадность выберешь сам
            1.0
        );
        auto newGraph1 = ac->distributePassengers();
        auto point = calcArea.calcPoints(newGraph1);
        auto area1 = Area(point);
        area1.setTAccessibility(area1.calcTime(newGraph1));
        if (area1.taccessibil < area.taccessibil)
        {
            area = area1;
            newGraph = newGraph1;
            points = point; // сделать вывод зон
        }
    }

    qDebug() << area.taccessibil;
    qDebug() << "NewAirportsWorker все посчитал";

    /// в этом месте меняешь graph на свой граф который у тебя оказался
    /// оптимальным в результате перебора
    ///
    /// после вычислений так сохранишь оптимальный граф
    settingsRepository->setJson("airportss5", newGraph.toJson());
    /// тут граф передается в интерфейс для отображения
    emit resultReady("s5", newGraph);
    emit onAllCalculated();
}
