//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_GETAIRPORTSWORKER_H
#define AVIA_GETAIRPORTSWORKER_H


#include <QThread>
#include "src/data/db/dbconnector/modelfactory/flightmodelsfactory/FlightModelsFactory.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"

class GetAirportsWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;
    FlightModelsFactory *factory = new FlightModelsFactory();
    QHash<QString, AirportModel> airports;

public:

    GetAirportsWorker(
            QString uriStr
    ) {
        this->uriString = uriStr;
    }

    ~GetAirportsWorker() {
        delete factory;
    }

    void run() override;

signals:
    void resultReady(QList<AirportModel> airports);
    void onChangeProgress(int progress);
};

#endif //AVIA_GETAIRPORTSWORKER_H
