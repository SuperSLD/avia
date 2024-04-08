//
// Created by Леонид Соляной on 04.04.2024.
//

#ifndef AVIA_BASEDBMODELFACTORY_H
#define AVIA_BASEDBMODELFACTORY_H

#include <QObject>
#include <QJsonObject>
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"
#include "src/data/db/dbconnector/DBConnector.h"

/**
 * Базовый класс для доступа к данным из таблицы.
 */
class BaseDBModelFactory: public QObject {
    Q_OBJECT

protected:
    DBConnector *dbConnector;

public:
    BaseDBModelFactory();
    ~BaseDBModelFactory();

    virtual BaseDBModel* createModel(QJsonObject json);
    virtual QString tableName();

    void setConnector(DBConnector *dbConnector);
};

#endif //AVIA_BASEDBMODELFACTORY_H
