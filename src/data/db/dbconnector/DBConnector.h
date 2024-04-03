//
// Created by Леонид Соляной on 31.03.2024.
//

#ifndef AVIA_DBCONNECTOR_H
#define AVIA_DBCONNECTOR_H

#include <QString>

class DBConnector {

private:
    QString url;
    QString user;
    QString password;

public:
    DBConnector(QString url, QString user, QString password);
    ~DBConnector();

    bool isConnected();
};

#endif //AVIA_DBCONNECTOR_H
