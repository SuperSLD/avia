//
// Created by Леонид Соляной on 31.03.2024.
//

#ifndef AVIA_DBCONNECTOR_H
#define AVIA_DBCONNECTOR_H

#include <QString>
#include <QThread>
#include <QList>
#include <QJsonArray>
#include "src/data/db/dbconnector/workers/getpage/GetPageWorker.h"
#include "src/data/db/dbconnector/workers/checkconnection/CheckConnectionWorker.h"
#include "src/data/db/dbconnector/workers/getanalytics/GetAnalyticsWorker.h"
#include "src/domain/models/analytics/AnalyticsModel.h"
#include "src/data/db/dbconnector/workers/getallroutes/GetAllRoutesWorker.h"
#include "src/data/db/dbconnector/workers/getairports/GetAirportsWorker.h"

class DBConnector: public QObject {
    Q_OBJECT
private:
    QString url;
    QString user;
    QString password;

    CheckConnectionWorker *checkConnectionWorker;
    GetPageWorker *getPageWorker;
    GetAnalyticsWorker *getAnalyticsWorker;
    bool getAnalyticsWorkerIsStart = false;
    GetAllRoutesWorker *getAllRoutesWorker;
    bool getAllRoutesWorkerIsStart = false;
    GetAirportsWorker *getAirportsWorker;
    bool getAirportsWorkerIsStart = false;

public:
    DBConnector(QString url, QString user, QString password);
    ~DBConnector();

    bool dataEquals(QString url, QString user, QString password);

    void checkConnection();

    void loadPage(QString table, int page, int pageSize);

    void loadAnalytics();
    bool analyticsLoadingInProgress();

    void loadRoutes();
    bool routesLoadingInProgress();

    void loadAirports();

private slots:
    void handleConnectionChecked(bool isConnected);

    void handleLoadedPage(QJsonArray array, QString table);

    void handleAnalyticsLoaded(AnalyticsModel analyticsModel);
    void handleAnalyticsLoadedProgress(int progress);

    void handleRoutesLoaded(QList<RouteModel*> routes);
    void handleAllRoutesLoadedProgress(int progress);

    void handleAirportsLoaded(QList<AirportModel> airports);
    void handleAirportsLoadedProgress(int progress);

signals:
    void onConnectionChecked(bool isConnected);

    void onPageLoaded(QJsonArray array, QString table);

    void onAnalyticsLoded(AnalyticsModel analyticsModel);
    void onChangeAnalyticsLoadedProgress(int progress);

    void onRoutesLoaded(QList<RouteModel*> routes);
    void onChangeRoutesLoadedProgress(int progress);

    void onAirportsLoaded(QList<AirportModel> airports);
    void onChangeAirportsLoadedProgress(int progress);
};

#endif //AVIA_DBCONNECTOR_H
