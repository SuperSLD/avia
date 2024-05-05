//
// Created by Леонид Соляной on 06.05.2024.
//

#ifndef AVIA_GEOMETRY_H
#define AVIA_GEOMETRY_H

#include <math.h>

namespace geometry {

    static const double EARTH_RADIUS = 6371.0;
    static const double PI = 3.14;

    static double degToRad(double deg) {
        return deg * PI / 180.0;
    }

    static double distanceInKm(double lon1, double lat1, double lon2, double lat2) {
        auto cosD = sin(degToRad(lat1)) * sin(degToRad(lat2)) + cos(degToRad(lat1)) * cos(degToRad(lat2)) * cos(degToRad(lon1) - degToRad(lon2));
        auto D = acos(cosD);
        return D * EARTH_RADIUS;
    }
}

#endif //AVIA_GEOMETRY_H
