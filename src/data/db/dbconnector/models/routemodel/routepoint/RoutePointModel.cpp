//
// Created by Леонид Соляной on 09.04.2024.
//

#include "RoutePointModel.h"

RoutePointModel::RoutePointModel(
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
) {
    this->fid = fid;
    this->svd = svd;
    this->lat = lat;
    this->lon = lon;
    this->fal = fal;
    this->altbaro =  altbaro;
    this->altgps =  altgps;
    this->fhd =  fhd;
    this->fvr =  fvr;
    this->so =  so;
    this->wxairtemp =  wxairtemp;
    this->wxspd =  wxspd;
    this->wxwrid =  wxwrid;
    this->nvapr =  nvapr;
    this->nvalthld =  nvalthld;
    this->nvaltmcp =  nvaltmcp;
    this->nvapt =  nvapt;
    this->nvlnav =  nvlnav;
    this->nvvnav =  nvvnav;
    this->nvtcas =  nvtcas;
    this->nacp =  nacp;
    this->nacv =  nacv;
    this->nic =  nic;
    this->nicbaro =  nicbaro;
    this->sil =  sil;
    this->siltype =  siltype;
}