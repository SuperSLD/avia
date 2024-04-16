//
// Created by Леонид Соляной on 16.04.2024.
//

#ifndef AVIA_GETALLROUTESWORKER_H
#define AVIA_GETALLROUTESWORKER_H


#include <QThread>
#include "src/data/db/dbconnector/modelfactory/routesmodelfactory/RoutesModelFactory.h"
#include "src/data/db/dbconnector/models/routemodel/RouteModel.h"

class GetAllRoutesWorker: public QThread {
    Q_OBJECT

private:
    const int LOADING_LIMIT = 1000;//2000;

    QString uriString;
    RoutesModelFactory *factory = new RoutesModelFactory();

public:

    GetAllRoutesWorker(
            QString uriStr
    ) {
        this->uriString = uriStr;
    }

    ~GetAllRoutesWorker() {
        delete factory;
    }

    void run() override;

signals:
    void resultReady(QList<RouteModel*> routes);
    void onChangeProgress(int progress);
};


#endif //AVIA_GETALLROUTESWORKER_H
