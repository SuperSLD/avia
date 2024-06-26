//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_FLIGHTDATAMODEL_H
#define AVIA_FLIGHTDATAMODEL_H


#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

class FlightDataModel: public BaseDBModel {

public:
    QString fid;
    int accl;
    QString accountry;
    QString acd;
    QString acr;
    QString act;
    QString alia;
    QString alic;
    QString alna;
    int alt;
    QString apdstci;
    QString apdstco;
    QString apdstia;
    QString apdstic;
    double apdstla;
    double apdstlo;
    QString apdstna;
    QString apdstst;
    int apdsttz;
    QString apdsttznl;
    QString apdsttzns;
    QString aporgci;
    QString aporgco;
    QString aporgia;
    QString aporgic;
    double aporgla;
    double aporglo;
    QString aporgna;
    QString aporgst;
    int aporgtz;
    QString aporgtznl;
    QString aporgtzns;
    QString arrau;
    QString arrdeld;
    QString arrdelr;
    QString arrdels;
    QString arre;
    QString arresu;
    QString arrgate;
    QString arrs;
    QString arrsu;
    QString arrterm;
    bool bl;
    QString cancel;
    QString codeshares;
    QString cs;
    QString csalia;
    QString csalic;
    QString csalna;
    QString depau;
    QString depchec;
    QString depdeld;
    QString depdelr;
    QString depdels;
    QString depe;
    QString depeu;
    QString depgate;
    QString deps;
    int depsu;
    QString depterm;
    double firstla;
    QString firstlaloci;
    QString firstlaloco;
    QString firstlalost;
    QString firstlalot;
    double firstlo;
    QString fnia;
    QString fnic;
    bool ground;
    int hd;
    QString la;
    double lastla;
    QString lastlaloci;
    QString lastlaloco;
    QString lastlaloso;
    QString lastlalost;
    QString lastlalot;
    double lastlo;
    QString lngt;
    QString lo;
    QString mrgarrs;
    QString mrgarru;
    QString mrgdeps;
    QString mrgdepu;
    QString ms;
    bool onflights;
    QString so;
    QString st;
    QString svd;
    QString pcnt;
    QString accn;
    QString departure;
    QString departure_meta;
    QString arrival;
    QString arrival_meta;
    QString status;
    QString delay;
    QString arrdelay;
    QString depdelay;
    QString progress;
    QString duration;
    int durationTs;
    QString durationType;
    QString distance;
    QString lastlalotRelative;
    QString departureRelative;
    QString arrivalRelative;
    QString text;
    QString bg;
    QString label;
    QString depsts;
    QString depc;
    QString arrsts;
    QString arrc;
    QString deps_utc;
    QString arrival_utc;
    QString arrs_utc;
    QString year;
    QString day;
    QString depdate;
    QString year_utc;
    QString day_utc;
    QString depdate_utc;
    QString arrdate;
    QString arrdateShort;
    QString arrdate_utc;
    QString arrdateShort_utc;
    bool replay;
    bool isFuture;

    FlightDataModel(
            QString fid,
            int accl,
            QString accountry,
            QString acd,
            QString acr,
            QString act,
            QString alia,
            QString alic,
            QString alna,
            int alt,
            QString apdstci,
            QString apdstco,
            QString apdstia,
            QString apdstic,
            double apdstla,
            double apdstlo,
            QString apdstna,
            QString apdstst,
            int apdsttz,
            QString apdsttznl,
            QString apdsttzns,
            QString aporgci,
            QString aporgco,
            QString aporgia,
            QString aporgic,
            double aporgla,
            double aporglo,
            QString aporgna,
            QString aporgst,
            int aporgtz,
            QString aporgtznl,
            QString aporgtzns,
            QString arrau,
            QString arrdeld,
            QString arrdelr,
            QString arrdels,
            QString arre,
            QString arresu,
            QString arrgate,
            QString arrs,
            QString arrsu,
            QString arrterm,
            bool bl,
            QString cancel,
            QString codeshares,
            QString cs,
            QString csalia,
            QString csalic,
            QString csalna,
            QString depau,
            QString depchec,
            QString depdeld,
            QString depdelr,
            QString depdels,
            QString depe,
            QString depeu,
            QString depgate,
            QString deps,
            int depsu,
            QString depterm,
            double firstla,
            QString firstlaloci,
            QString firstlaloco,
            QString firstlalost,
            QString firstlalot,
            double firstlo,
            QString fnia,
            QString fnic,
            bool ground,
            int hd,
            QString la,
            double lastla,
            QString lastlaloci,
            QString lastlaloco,
            QString lastlaloso,
            QString lastlalost,
            QString lastlalot,
            double lastlo,
            QString lngt,
            QString lo,
            QString mrgarrs,
            QString mrgarru,
            QString mrgdeps,
            QString mrgdepu,
            QString ms,
            bool onflights,
            QString so,
            QString st,
            QString svd,
            QString pcnt,
            QString accn,
            QString departure,
            QString departure_meta,
            QString arrival,
            QString arrival_meta,
            QString status,
            QString delay,
            QString arrdelay,
            QString depdelay,
            QString progress,
            QString duration,
            int durationTs,
            QString durationType,
            QString distance,
            QString lastlalotRelative,
            QString departureRelative,
            QString arrivalRelative,
            QString text,
            QString bg,
            QString label,
            QString depsts,
            QString depc,
            QString arrsts,
            QString arrc,
            QString deps_utc,
            QString arrival_utc,
            QString arrs_utc,
            QString year,
            QString day,
            QString depdate,
            QString year_utc,
            QString day_utc,
            QString depdate_utc,
            QString arrdate,
            QString arrdateShort,
            QString arrdate_utc,
            QString arrdateShort_utc,
            bool replay,
            bool isFuture
    );

    FlightDataModel() {}

    bool inRussia();
};


#endif //AVIA_FLIGHTDATAMODEL_H
