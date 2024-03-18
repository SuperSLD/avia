//
// Created by Леонид Соляной on 04.02.2024.
//

#include "SettingsRepository.h"

SettingsRepository::SettingsRepository() {
    settings = new QSettings("settings.ini", QSettings::IniFormat);
}

SettingsRepository::~SettingsRepository() {
    delete settings;
}

void SettingsRepository::setTheme(bool isLight) {
    settings->setValue("theme", isLight);
    settings->sync();
}

bool SettingsRepository::getTheme() {
    return settings->value("theme").toBool();
}

void SettingsRepository::saveConnections() {
    //settings->setValue("token", token);
    //settings->sync();
}

QList<QString> SettingsRepository::getConnections() {
    //return settings->value("token", "").toString();
    return QList<QString>();
}
