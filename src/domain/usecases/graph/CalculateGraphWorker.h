//
// Created by Леонид Соляной on 17.04.2024.
//

#ifndef AVIA_CALCULATEGRAPHWORKER_H
#define AVIA_CALCULATEGRAPHWORKER_H


#include <QThread>
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"

class CalculateGraphWorker: public QThread {
Q_OBJECT

private:
    QString uriString;
    QList<AirportModel> airports;

public:
    CalculateGraphWorker(QString uri, QList<AirportModel> airports) {
        this->uriString = uri;
        this->airports = airports;
    }

    void run() override;

signals:
    void resultReady();
};

#endif //AVIA_CALCULATEGRAPHWORKER_H
