//
// Created by Леонид Соляной on 31.03.2024.
//

#ifndef AVIA_DBCONNECTOR_H
#define AVIA_DBCONNECTOR_H

#include <QString>
#include <QThread>

class DBConnector: public QObject {
    Q_OBJECT
private:
    QString url;
    QString user;
    QString password;

public:
    DBConnector(QString url, QString user, QString password);
    ~DBConnector();

    void checkConnection();

private slots:
    void handleConnectionChecked(bool isConnected);

signals:
    void onConnectionChecked(bool isConnected);
};

#endif //AVIA_DBCONNECTOR_H
