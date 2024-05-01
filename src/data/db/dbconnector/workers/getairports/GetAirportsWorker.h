//
// Created by Леонид Соляной on 21.04.2024.
//

#ifndef AVIA_GETAIRPORTSWORKER_H
#define AVIA_GETAIRPORTSWORKER_H


#include <QThread>
#include "src/data/db/dbconnector/modelfactory/flightmodelsfactory/FlightModelsFactory.h"
#include "src/data/db/dbconnector/models/airportmodel/AirportModel.h"
#include "src/domain/models/transportgraph/TransportGraphModel.h"
#include "src/data/settings/SettingsRepository.h"

class GetAirportsWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;
    FlightModelsFactory *factory = new FlightModelsFactory();
    QHash<QString, AirportModel> airports;

    SettingsRepository *settingsRepository;

public:

    GetAirportsWorker(
            QString uriStr
    ) {
        this->uriString = uriStr;
        settingsRepository = new SettingsRepository();
    }

    ~GetAirportsWorker() {
        delete factory;
        delete settingsRepository;
    }

    void run() override;

signals:
    void resultReady(TransportGraphModel graph, bool fromDB);
    void onChangeProgress(int progress);
};

#endif //AVIA_GETAIRPORTSWORKER_H
