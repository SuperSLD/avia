//
// Created by Егор Рыжов on 16.05.2024.
//

#ifndef ATIME_H
#define ATIME_H

#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class ATime: public BaseModel {

public:
    QString id;
    double aTime;
    int count;

    ATime(
        QString id,
        double aTime,
        int count
    );
};

#endif //ATIME_H
