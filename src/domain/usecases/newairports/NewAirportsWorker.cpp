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
    //SLY   1
    zamena.append(QString("SLY"));
    newAirports.append(AirportModel("USDA", "Sabetta", "Sabetta", 72.03889, 71.21444, 5249, 5249, {}));
    //PWE   2
    zamena.append(QString("PWE"));
    newAirports.append(AirportModel("UHMB", "Baranikha", "Bilibino", 168.25738, 68.49535, 250, 250, {}));
    //NSK   3
    zamena.append(QString("NSK"));
    newAirports.append(AirportModel("USDM", "Utrenniy", "Utrenniy", 74.25971, 71.01116, 2557, 2557, {}));
    //PWE   4
    zamena.append(QString("PWE"));
    newAirports.append(AirportModel("UESS", "Cherskyi", "Cherskyi", 161.33972, 68.74128, 250, 250, {}));
    //NSK   5
    zamena.append(QString("NSK"));
    newAirports.append(AirportModel("UODD", "Dikson", "Dikson", 80.37941, 73.51784, 2843, 2843, {}));
    //PWE   6
    zamena.append(QString("PWE"));
    newAirports.append(AirportModel("UESA", "Andryushkino", "Andryushkino", 154.4608, 69.17023, 250, 250, {}));
    //NSK   7
    zamena.append(QString("NSK"));
    newAirports.append(AirportModel("UODL", "Mys Chelyuskin", "Mys Chelyuskin", 104.71370, 77.71370, 2377, 2377, {}));
    //YKS   8
    zamena.append(QString("YKS"));
    newAirports.append(AirportModel("UEBE", "Tenkeli", "Deputatskiy", 140.70743, 70.16503, 5284, 5284, {}));
    //NSK   9
    zamena.append(QString("NSK"));
    newAirports.append(AirportModel("UOHH", "Khatanga", "Khatanga", 102.49318, 71.9784, 3289, 3289, {}));
    //YKS   10
    zamena.append(QString("YKS"));
    newAirports.append(AirportModel("UEBK", "Kular", "Kazachie", 134.50997, 70.59633, 5191, 5191, {}));
    //NSK   11
    zamena.append(QString("NSK"));
    newAirports.append(AirportModel("UOHK", "Mys Kosistiy", "Mys Kosistiy", 109.75975, 73.66215, 3785, 3785, {}));
    //YKS   12
    zamena.append(QString("YKS"));
    newAirports.append(AirportModel("UESB", "Bulun", "Kusur", 127.3955, 70.69823, 5825, 5825, {}));
    //MJZ   13
    zamena.append(QString("MJZ"));
    newAirports.append(AirportModel("UERB", "Anabar", "Ebelyah", 113.5808, 70.88308, 4714, 4714, {}));
    //MJZ   14
    zamena.append(QString("MJZ"));
    newAirports.append(AirportModel("UETT", "Taymylyr", "Taymylyr", 121.8716, 72.62633, 5498, 5498, {}));

   graph.airports.append(newAirports[0]);
    int ind = 1000;
    for (int i=0; i < graph.airports.size(); i++)
    {
        if (graph.airports[i].id == zamena[0])
        {
            ind = i;
        }
    }
    if (ind <1000)
    {
        graph.airports[ind].passengersCountIn = graph.airports[ind].passengersCountIn - newAirports[0].passengersCountIn;
        graph.airports[ind].passengersCountOut = graph.airports[ind].passengersCountOut - newAirports[0].passengersCountOut;
    }

    /// посчитанные зоны доступности
    //auto area = Area(settingsRepository->getJson("area"));

    /// пример того как пользоваться муравьиным алгоритмом
    emit onChangeProgress(1);
    auto *aco = new AntColonyOptimization(
            "s5",
            graph.airports,
            0.3, // жадность выберешь сам
            1.2, // стадность выберешь сам
            1.0
    );

    auto newGraph = aco->distributePassengers();
    auto calcArea = CalcNewArea();
    auto points = calcArea.calcPoints(newGraph);

    auto area = Area(points);
    area.setTAccessibility(area.calcTime(newGraph));
    double time = 20;
    int kolichestvo = 0;

    for (int i=1; i < newAirports.size(); i++)
    {
        graph.airports.append(newAirports[i]);
        emit onChangeProgress(i+1);
        int ind = 1000;
        for (int j=0; j < graph.airports.size(); j++)
        {
            if (graph.airports[j].id == zamena[i])
            {
                ind = i;
            }
        }
        if (ind <1000)
        {
            graph.airports[ind].passengersCountIn = graph.airports[ind].passengersCountIn - newAirports[i].passengersCountIn;
            graph.airports[ind].passengersCountOut = graph.airports[ind].passengersCountOut - newAirports[i].passengersCountOut;
        }
        if (i > 6)
        {
            auto *ac = new AntColonyOptimization(
            "s5",
            graph.airports,
            0.3, // жадность
            1.2, // стадность
            1.0
            );
            auto newGraph1 = ac->distributePassengers();
            auto point = calcArea.calcPoints(newGraph1);
            auto area1 = Area(point);
            area1.setTAccessibility(area1.calcTime(newGraph1));
            if (area1.taccessibil < time )
            {
                kolichestvo = i + 1;
                area = area1;
                newGraph = newGraph1;
                points = point; // сделать вывод зон
                time = area1.taccessibil;
            }
        }
    }

    qDebug() << area.taccessibil;
    qDebug() << "Количество аэропортов" << kolichestvo;
    qDebug() << "Количество секторов: " << area.pointsCount;
    qDebug() << "Максимальное расстояние до аэропорта: " << area.maxDistance;
    qDebug() << "Максимальное время в пути: " << area.maxTime;
    qDebug() << "NewAirportsWorker все посчитал";

    /// в этом месте меняем graph на свой граф который у нас оказался
    /// оптимальным в результате перебора
    ///
    /// после вычислений так сохраняем оптимальный граф
    settingsRepository->setJson("airportss5", newGraph.toJson());
    /// тут граф передается в интерфейс для отображения
    emit resultReady("s5", newGraph);
    emit onAllCalculated();
}
