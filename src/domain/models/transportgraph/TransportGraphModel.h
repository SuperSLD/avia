//
// Created by Леонид Соляной on 22.04.2024.
//

#ifndef AVIA_TRANSPORTGRAPHMODEL_H
#define AVIA_TRANSPORTGRAPHMODEL_H


#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/models/analytics/BaseAnalyticModel.h"
#include "src/domain/models/analytics/view/chart/ChartLine.h"

class TransportGraphModel: public BaseAnalyticModel {

private:
    void calcDataForView();
    void calcAnalyticData();

public:
    QList<AirportModel> airports;
    int    maxAirportFlightCount = 0;
    QList<QList<double>> viewLines;
    QList<double> viewLinesPassCount;
    double lineMaxCount = 0.0;

    /// жадность
    double greed = 1.0;
    /// стадность
    double gregariousness = 1.0;
    /// средняя длинна маршрута по прямой
    double midFlightDistance = 0.0;
    /// среднее время
    double midTime = 0.0;
    /// средняя длинна маршрута
    double midRealDistance = 0.0;
    /// коэффициент непрямолинейности маршрутов
    double nonStraightness = 0.0;
    /// название сохранения
    QString save = "s0";
    /// распределение самолетов по типам
    QHash<QString, int> aircraftCount;
    /// общее количество самолетов
    double allTypesCount = 0;
    /// среднее количество пассажиров на рейсе
    double midPassCount = 0.0;
    /// стоимость перевозок
    double cost = 0.0;
    /// часть распределенных пассажиров
    double part = 1.0;
    /// суммарная дальность перевозок до
    /// главного транспортного узла
    double sumDistance = 0.0;
    /// общее количество пассажиров
    double totalPassCount = 0.0;
    /// общее количество пассажиров
    double totalPassCountInOut = 0.0;

    /// макс параметры для нормирования
    double maxP1 = -1;
    double maxP2 = -1;
    double maxP3 = -1;

    qint64 passCount = 0;
    QList<ChartLine> passCountPieChart;

    AirportModel mainTransportNode;

    TransportGraphModel(QList<AirportModel> airports, QString save = "s0", double greed = 1.0, double gregariousness = 1.0, double cost = 1, double part = 1.0);
    TransportGraphModel(QJsonObject json);
    TransportGraphModel() {}

    TransportGraphModel getWithEmptyEdges();

    AirportModel getMinDistanceAirport(double lon, double lat);
    AirportModel findAirport(QString id);

    QJsonObject toJson() override;

    QList<AnalyticsRow> getRows(bool isSingle = true) override;

    bool hasConnection(QString from, QString to, QList<QString> visited = {});

    /**
     * Алгоритм A-star для поиска оптимальногом аршрута
     * из начального аэропорта в конечный.
     * @param from начальный аэропорт.
     * @param to конечный аэропорт.
     * @return путь из начального аэропорта в конечный.
     */
    QList<QString> findPath(QString from, QString to);
    QList<QString> reconstructPath(QHash<QString, QString> cameFrom, QString from, QString to);
    double pathSize(QList<QString> path);

    void setAircraftCount(QHash<QString, int> aircraftCount);

    double crit(
            bool isHub,
            double plot,
            double maxNonStraightness,
            double minNonStraightness,
            double maxPlot,
            double minPlot,
            double maxMidTime
    );
};


#endif //AVIA_TRANSPORTGRAPHMODEL_H
