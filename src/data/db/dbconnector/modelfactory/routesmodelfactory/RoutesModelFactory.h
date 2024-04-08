//
// Created by Леонид Соляной on 09.04.2024.
//

#ifndef AVIA_ROUTESMODELFACTORY_H
#define AVIA_ROUTESMODELFACTORY_H

#include "src/data/db/dbconnector/modelfactory/BaseDBModelFactory.h"

class RoutesModelFactory: public BaseDBModelFactory {

public:
    RoutesModelFactory();
    ~RoutesModelFactory();

    BaseDBModel* createModel(QJsonObject json) override;
    QString tableName() override;
};

#endif //AVIA_ROUTESMODELFACTORY_H
