//
// Created by Егор Рыжов on 16.05.2024.
//

#ifndef TACCESSIBILITY_H
#define TACCESSIBILITY_H

#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"


class TAccessibility: public BaseModel {

public:
    QString id;
    double tAccessibility;

    TAccessibility(
        QString id,
        double tAccessibility
    );
};

#endif //TACCESSIBILITY_H
