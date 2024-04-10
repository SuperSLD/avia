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

class DBConnector: public QObject {
    Q_OBJECT
private:
    QString url;
    QString user;
    QString password;

    CheckConnectionWorker *checkConnectionWorker;
    GetPageWorker *getPageWorker;
    GetAnalyticsWorker *getAnalyticsWorker;

public:
    DBConnector(QString url, QString user, QString password);
    ~DBConnector();

    bool dataEquals(QString url, QString user, QString password);
    void checkConnection();
    void loadPage(QString table, int page, int pageSize);
    void loadAnalytics();
    bool analyticsLoadingInProgress();

private slots:
    void handleConnectionChecked(bool isConnected);
    void handleLoadedPage(QJsonArray array, QString table);
    void handleAnalyticsLoaded(AnalyticsModel analyticsModel);
    void handleAnalyticsLoadedProgress(int progress);

signals:
    void onConnectionChecked(bool isConnected);
    void onPageLoaded(QJsonArray array, QString table);
    void onAnalyticsLoded(AnalyticsModel analyticsModel);
    void onChangeAnalyticsLoadedProgress(int progress);
};

#endif //AVIA_DBCONNECTOR_H
