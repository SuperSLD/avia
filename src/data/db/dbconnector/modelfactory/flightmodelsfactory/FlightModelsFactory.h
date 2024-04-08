//
// Created by Леонид Соляной on 04.04.2024.
//

#ifndef AVIA_FLIGHTMODELSFACTORY_H
#define AVIA_FLIGHTMODELSFACTORY_H

#include "src/data/db/dbconnector/modelfactory/BaseDBModelFactory.h"

class FlightModelsFactory: public BaseDBModelFactory {

public:
    FlightModelsFactory();
    ~FlightModelsFactory();

    BaseDBModel* createModel(QJsonObject json) override;
    QString tableName() override;
};


#endif //AVIA_FLIGHTMODELSFACTORY_H
