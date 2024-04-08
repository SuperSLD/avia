//
// Created by Леонид Соляной on 09.04.2024.
//

#ifndef AVIA_ROUTEPOINTMODEL_H
#define AVIA_ROUTEPOINTMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class RoutePointModel: public BaseDBModel {

public:
    QString fid;
    QString svd;
    double lat;
    double lon;
    int fal;
    int altbaro;
    int altgps;
    int fhd;
    int fvr;
    QString so;
    int wxairtemp;
    int wxspd;
    int wxwrid;
    QString nvapr;
    QString nvalthld;
    int nvaltmcp;
    QString nvapt;
    bool nvlnav;
    bool nvvnav;
    bool nvtcas;
    int nacp;
    int nacv;
    int nic;
    int nicbaro;
    int sil;
    QString siltype;

    RoutePointModel(
            QString fid,
            QString svd,
            double lat,
            double lon,
            int fal,
            int altbaro,
            int altgps,
            int fhd,
            int fvr,
            QString so,
            int wxairtemp,
            int wxspd,
            int wxwrid,
            QString nvapr,
            QString nvalthld,
            int nvaltmcp,
            QString nvapt,
            bool nvlnav,
            bool nvvnav,
            bool nvtcas,
            int nacp,
            int nacv,
            int nic,
            int nicbaro,
            int sil,
            QString siltype
    );

    RoutePointModel() {};
};


#endif //AVIA_ROUTEPOINTMODEL_H
