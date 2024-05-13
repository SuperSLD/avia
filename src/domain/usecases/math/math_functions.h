//
// Created by Леонид Соляной on 06.05.2024.
//

#ifndef AVIA_MATH_FUNCTIONS_H
#define AVIA_MATH_FUNCTIONS_H

#include <math.h>

namespace math_functions {

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

    static int randInRange(int min, int max) {
        return min + (std::rand() % (max - min + 1));
    }

    static double randInRange(double fMin, double fMax) {
        double f = (double) rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
}

#endif //AVIA_MATH_FUNCTIONS_H
