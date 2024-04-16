//
// Created by Леонид Соляной on 09.04.2024.
//

#include "RoutesModelFactory.h"
#include "src/data/db/dbconnector/models/routemodel/RouteModel.h"

RoutesModelFactory::RoutesModelFactory() {

}

RoutesModelFactory::~RoutesModelFactory() {

}

BaseDBModel* RoutesModelFactory::createModel(QJsonObject json) {
    auto data = json["data"].toObject();
    auto current = data["current"].toObject();
    auto list = data["list"].toArray();
    QList<RoutePointModel> pointList;
    foreach(QJsonValue val, list) {
        auto obj = val.toObject();
        pointList.append(
            RoutePointModel(
                obj["fid"].toString(),
                obj["svd"].toString(),
                obj["lat"].toDouble(),
                obj["lon"].toDouble(),
                obj["fal"].toInt(),
                obj["altbaro"].toInt(),
                obj["altgps"].toInt(),
                obj["fhd"].toInt(),
                obj["fvr"].toInt(),
                obj["so"].toString(),
                obj["wxairtemp"].toInt(),
                obj["wxspd"].toInt(),
                obj["wxwrid"].toInt(),
                obj["nvapr"].toString(),
                obj["nvalthld"].toString(),
                obj["nvaltmcp"].toInt(),
                obj["nvapt"].toString(),
                obj["nvlnav"].toBool(),
                obj["nvvnav"].toBool(),
                obj["nvtcas"].toBool(),
                obj["nacp"].toInt(),
                obj["nacv"].toInt(),
                obj["nic"].toInt(),
                obj["nicbaro"].toInt(),
                obj["sil"].toInt(),
                obj["siltype"].toString()
            )
        );
    }
    return new RouteModel(
            json,
            json["_id"].toObject()["$oid"].toString(),
            json["fnia"].toString(),
            json["fid"].toString(),
            RouteDataModel(
                FlightDataModel(
                        current["fid"].toString(),
                        current["accl"].toInt(),
                        current["accountry"].toString(),
                        current["acd"].toString(),
                        current["acr"].toString(),
                        current["act"].toString(),
                        current["alia"].toString(),
                        current["alic"].toString(),
                        current["alna"].toString(),
                        current["alt"].toInt(),
                        current["apdstci"].toString(),
                        current["apdstco"].toString(),
                        current["apdstia"].toString(),
                        current["apdstic"].toString(),
                        current["apdstla"].toDouble(),
                        current["apdstlo"].toDouble(),
                        current["apdstna"].toString(),
                        current["apdstst"].toString(),
                        current["apdsttz"].toInt(),
                        current["apdsttznl"].toString(),
                        current["apdsttzns"].toString(),
                        current["aporgci"].toString(),
                        current["aporgco"].toString(),
                        current["aporgia"].toString(),
                        current["aporgic"].toString(),
                        current["aporgla"].toDouble(),
                        current["aporglo"].toDouble(),
                        current["aporgna"].toString(),
                        current["aporgst"].toString(),
                        current["aporgtz"].toInt(),
                        current["aporgtznl"].toString(),
                        current["aporgtzns"].toString(),
                        current["arrau"].toString(),
                        current["arrdeld"].toString(),
                        current["arrdelr"].toString(),
                        current["arrdels"].toString(),
                        current["arre"].toString(),
                        current["arresu"].toString(),
                        current["arrgate"].toString(),
                        current["arrs"].toString(),
                        current["arrsu"].toString(),
                        current["arrterm"].toString(),
                        current["bl"].toBool(),
                        current["cancel"].toString(),
                        current["codeshares"].toString(),
                        current["cs"].toString(),
                        current["csalia"].toString(),
                        current["csalic"].toString(),
                        current["csalna"].toString(),
                        current["depau"].toString(),
                        current["depchec"].toString(),
                        current["depdeld"].toString(),
                        current["depdelr"].toString(),
                        current["depdels"].toString(),
                        current["depe"].toString(),
                        current["depeu"].toString(),
                        current["depgate"].toString(),
                        current["deps"].toString(),
                        current["depsu"].toInt(),
                        current["depterm"].toString(),
                        current["firstla"].toDouble(),
                        current["firstlaloci"].toString(),
                        current["firstlaloco"].toString(),
                        current["firstlalost"].toString(),
                        current["firstlalot"].toString(),
                        current["firstlo"].toDouble(),
                        current["fnia"].toString(),
                        current["fnic"].toString(),
                        current["ground"].toBool(),
                        current["hd"].toInt(),
                        current["la"].toString(),
                        current["lastla"].toDouble(),
                        current["lastlaloci"].toString(),
                        current["lastlaloco"].toString(),
                        current["lastlaloso"].toString(),
                        current["lastlalost"].toString(),
                        current["lastlalot"].toString(),
                        current["lastlo"].toDouble(),
                        current["lngt"].toString(),
                        current["lo"].toString(),
                        current["mrgarrs"].toString(),
                        current["mrgarru"].toString(),
                        current["mrgdeps"].toString(),
                        current["mrgdepu"].toString(),
                        current["ms"].toString(),
                        current["onflights"].toBool(),
                        current["so"].toString(),
                        current["st"].toString(),
                        current["svd"].toString(),
                        current["pcnt"].toString(),
                        current["accn"].toString(),
                        current["departure"].toString(),
                        current["departure_meta"].toString(),
                        current["arrival"].toString(),
                        current["arrival_meta"].toString(),
                        current["status"].toString(),
                        current["delay"].toString(),
                        current["arrdelay"].toString(),
                        current["depdelay"].toString(),
                        current["progress"].toString(),
                        current["duration"].toString(),
                        current["durationTs"].toString(),
                        current["durationType"].toString(),
                        current["distance"].toString(),
                        current["lastlalotRelative"].toString(),
                        current["departureRelative"].toString(),
                        current["arrivalRelative"].toString(),
                        current["text"].toString(),
                        current["bg"].toString(),
                        current["label"].toString(),
                        current["depsts"].toString(),
                        current["depc"].toString(),
                        current["arrsts"].toString(),
                        current["arrc"].toString(),
                        current["deps_utc"].toString(),
                        current["arrival_utc"].toString(),
                        current["arrs_utc"].toString(),
                        current["year"].toString(),
                        current["day"].toString(),
                        current["depdate"].toString(),
                        current["year_utc"].toString(),
                        current["day_utc"].toString(),
                        current["depdate_utc"].toString(),
                        current["arrdate"].toString(),
                        current["arrdateShort"].toString(),
                        current["arrdate_utc"].toString(),
                        current["arrdateShort_utc"].toString(),
                        current["replay"].toBool(),
                        current["isFuture"].toBool()
                ),
                pointList,
                data["type"].toString()
            )
    );
}

QString RoutesModelFactory::tableName() {
    return "flights_routes";
}
