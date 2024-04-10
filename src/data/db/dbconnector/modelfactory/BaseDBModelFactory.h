//
// Created by Леонид Соляной on 04.04.2024.
//

#ifndef AVIA_BASEDBMODELFACTORY_H
#define AVIA_BASEDBMODELFACTORY_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

/**
 * Базовый класс для доступа к данным из таблицы.
 */
class BaseDBModelFactory: public QObject {
    Q_OBJECT

public:
    BaseDBModelFactory();
    ~BaseDBModelFactory();

    virtual BaseDBModel* createModel(QJsonObject json);
    virtual QString tableName();
};

#endif //AVIA_BASEDBMODELFACTORY_H
