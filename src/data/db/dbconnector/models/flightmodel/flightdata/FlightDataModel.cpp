//
// Created by Леонид Соляной on 08.04.2024.
//

#include "FlightDataModel.h"

FlightDataModel::FlightDataModel(
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
        QString durationTs,
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
) {
    this->fid = fid;
    this->accl = accl;
    this->accountry = accountry;
    this->acd = acd;
    this->acr = acr;
    this->act = act;
    this->alia = alia;
    this->alic = alic;
    this->alna = alna;
    this->alt = alt;
    this->apdstci = apdstci;
    this->apdstco = apdstco;
    this->apdstia = apdstia;
    this->apdstic = apdstic;
    this->apdstla = apdstla;
    this->apdstlo = apdstlo;
    this->apdstna = apdstna;
    this->apdstst = apdstst;
    this->apdsttz = apdsttz;
    this->apdsttznl = apdsttznl;
    this->apdsttzns = apdsttzns;
    this->aporgci = aporgci;
    this->aporgco = aporgco;
    this->aporgia = aporgia;
    this->aporgic = aporgic;
    this->aporgla = aporgla;
    this->aporglo = aporglo;
    this->aporgna = aporgna;
    this->aporgst = aporgst;
    this->aporgtz = aporgtz;
    this->aporgtznl = aporgtznl;
    this->aporgtzns = aporgtzns;
    this->arrau = arrau;
    this->arrdeld = arrdeld;
    this->arrdelr = arrdelr;
    this->arrdels = arrdels;
    this->arre = arre;
    this->arresu = arresu;
    this->arrgate = arrgate;
    this->arrs = arrs;
    this->arrsu = arrsu;
    this->arrterm = arrterm;
    this->bl = bl;
    this->cancel = cancel;
    this->codeshares = codeshares;
    this->cs = cs;
    this->csalia = csalia;
    this->csalic = csalic;
    this->csalna = csalna;
    this->depau = depau;
    this->depchec = depchec;
    this->depdeld = depdeld;
    this->depdelr = depdelr;
    this->depdels = depdels;
    this->depe = depe;
    this->depeu = depeu;
    this->depgate = depgate;
    this->deps = deps;
    this->depsu = depsu;
    this->depterm = depterm;
    this->firstla = firstla;
    this->firstlaloci = firstlaloci;
    this->firstlaloco = firstlaloco;
    this->firstlalost = firstlalost;
    this->firstlalot = firstlalot;
    this->firstlo = firstlo;
    this->fnia = fnia;
    this->fnic = fnic;
    this->ground = ground;
    this->hd = hd;
    this->la = la;
    this->lastla = lastla;
    this->lastlaloci = lastlaloci;
    this->lastlaloco = lastlaloco;
    this->lastlaloso = lastlaloso;
    this->lastlalost = lastlalost;
    this->lastlalot = lastlalot;
    this->lastlo = lastlo;
    this->lngt = lngt;
    this->lo = lo;
    this->mrgarrs = mrgarrs;
    this->mrgarru = mrgarru;
    this->mrgdeps = mrgdeps;
    this->mrgdepu = mrgdepu;
    this->ms = ms;
    this->onflights = onflights;
    this->so = so;
    this->st = st;
    this->svd = svd;
    this->pcnt = pcnt;
    this->accn = accn;
    this->departure = departure;
    this->departure_meta = departure_meta;
    this->arrival = arrival;
    this->arrival_meta = arrival_meta;
    this->status = status;
    this->delay = delay;
    this->arrdelay = arrdelay;
    this->depdelay = depdelay;
    this->progress = progress;
    this->duration = duration;
    this->durationTs = durationTs;
    this->durationType = durationType;
    this->distance = distance;
    this->lastlalotRelative = lastlalotRelative;
    this->departureRelative = departureRelative;
    this->arrivalRelative = arrivalRelative;
    this->text = text;
    this->bg = bg;
    this->label = label;
    this->depsts = depsts;
    this->depc = depc;
    this->arrsts = arrsts;
    this->arrc = arrc;
    this->deps_utc = deps_utc;
    this->arrival_utc = arrival_utc;
    this->arrs_utc = arrs_utc;
    this->year = year;
    this->day = day;
    this->depdate = depdate;
    this->year_utc = year_utc;
    this->day_utc = day_utc;
    this->depdate_utc = depdate_utc;
    this->arrdate = arrdate;
    this->arrdateShort = arrdateShort;
    this->arrdate_utc = arrdate_utc;
    this->arrdateShort_utc = arrdateShort_utc;
    this->replay = replay;
    this->isFuture = isFuture;
}
