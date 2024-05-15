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
    /// средняя длинна маршрута
    double midRealDistance = 0.0;
    /// коэффициент непрямолинейности маршрутов
    double nonStraightness = 0.0;

    QString save = "s0";

    qint64 passCount = 0;
    QList<ChartLine> passCountPieChart;

    AirportModel mainTransportNode;

    TransportGraphModel(QList<AirportModel> airports, QString save = "s0", double greed = 1.0, double gregariousness = 1.0);
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
};


#endif //AVIA_TRANSPORTGRAPHMODEL_H
