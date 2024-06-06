//
// Created by Леонид Соляной on 03.06.2024.
//

#ifndef AVIA_NEWAIRPORTSWORKER_H
#define AVIA_NEWAIRPORTSWORKER_H


#include <QThread>
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/usecases/area/CalculateAreaWorker.h"

class NewAirportsWorker: public QThread {
    Q_OBJECT

private:
    TransportGraphModel graph;
    SettingsRepository *settingsRepository;

public:
    NewAirportsWorker(TransportGraphModel graph) {
        this->graph = graph;
        settingsRepository = new SettingsRepository();
    }

    ~NewAirportsWorker() {
        delete settingsRepository;
    }

    QList<AirportModel> newAirports;

    void run() override;

signals:
    void onAllCalculated();
    void resultReady(QString key, TransportGraphModel graph);
    void onChangeProgress(int progress);
};

#endif //AVIA_NEWAIRPORTSWORKER_H
