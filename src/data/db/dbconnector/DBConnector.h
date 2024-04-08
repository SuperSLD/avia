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

class DBConnector: public QObject {
    Q_OBJECT
private:
    QString url;
    QString user;
    QString password;

    CheckConnectionWorker *checkConnectionWorker;
    GetPageWorker *getPageWorker;

public:
    DBConnector(QString url, QString user, QString password);
    ~DBConnector();

    void checkConnection();
    void loadPage(QString table, int page, int pageSize);

private slots:
    void handleConnectionChecked(bool isConnected);
    void handleLoadedPage(QJsonArray array, QString table);

signals:
    void onConnectionChecked(bool isConnected);
    void onPageLoaded(QJsonArray array, QString table);
};

#endif //AVIA_DBCONNECTOR_H
