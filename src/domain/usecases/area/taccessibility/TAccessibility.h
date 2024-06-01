//
// Created by Егор Рыжов on 16.05.2024.
//

#ifndef TACCESSIBILITY_H
#define TACCESSIBILITY_H

#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"


class TAccessibility: public BaseModel {

public:
    double lon;
    double  lat;
    double tAccessibility;

    TAccessibility(
        double lon,
        double lat,
        double tAccessibility
    );
};

#endif //TACCESSIBILITY_H
