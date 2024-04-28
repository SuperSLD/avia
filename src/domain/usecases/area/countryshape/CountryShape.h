//
// Created by Леонид Соляной on 28.04.2024.
//

#ifndef AVIA_COUNTRYSHAPE_H
#define AVIA_COUNTRYSHAPE_H


#include <QString>
#include <QList>

class CountryShape {

public:
    double maxLon = -181;
    double maxLat = -91;
    double minLon = 181;
    double minLat = 91;

    CountryShape(QString name);
};


#endif //AVIA_COUNTRYSHAPE_H
