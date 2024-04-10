//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_GETANALYTICSWORKER_H
#define AVIA_GETANALYTICSWORKER_H

#include <QThread>
#include "src/data/db/dbconnector/modelfactory/flightmodelsfactory/FlightModelsFactory.h"
#include "src/domain/models/analytics/AnalyticsModel.h"


class GetAnalyticsWorker: public QThread {
    Q_OBJECT

private:
    QString uriString;
    FlightModelsFactory *factory = new FlightModelsFactory();

public:

    GetAnalyticsWorker(
            QString uriStr
    ) {
        this->uriString = uriStr;
    }

    ~GetAnalyticsWorker() {
        delete factory;
    }

    void run() override;

    signals:
        void resultReady(AnalyticsModel analyticsModel);
        void onChangeProgress(int progress);
};


#endif //AVIA_GETANALYTICSWORKER_H
