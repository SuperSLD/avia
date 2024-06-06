//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_AIRPORTMODEL_H
#define AVIA_AIRPORTMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"
#include "src/domain/models/transportgraph/aircraftmodels/Aircraft.h"

class AirportModel: public BaseDBModel{

public:

    /// код аэропорта
    QString id;
    /// название аэропорта
    QString name;
    /// город аэропорта
    QString city;
    /// долгота
    double lon;
    /// широта
    double lat;
    /// количество пассажиров на вылет
    long passengersCountOut;
    /// количество пассажиров на прибытие
    long passengersCountIn;
    /// соединенные маршрутной сетью аэропорты
    QList<QString> connectedAirports;
    /// количество пассажиров пролетевших выбранным рейсом
    QHash<QString, double> connectedPassCount;
    QHash<QString, Aircraft> connectedAircraft;
    /// количество вылетов и прилетов
    int flightCount = 1;

    AirportModel(
        QString id,
        QString name,
        QString city,
        double lon,
        double lat,
        long passengersCountOut,
        long passengersCountIn,
        QList<QString> connectedAirports
    );
    AirportModel(QJsonObject json);
    AirportModel() {};

    QString getId() override;

    void addConnection(QString id);
    void incFlight();
    void incPassengerCount(int count, bool in, QString key);

    QJsonObject toJson() override;

    AirportModel getWithEmptyEdges();
};


#endif //AVIA_AIRPORTMODEL_H
