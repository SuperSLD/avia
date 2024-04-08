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

void SettingsRepository::setConnectionIp(QString ip) {
    settings->setValue("ip", ip);
    settings->sync();
}

QString SettingsRepository::getConnectionIp() {
    return settings->contains("ip") ? settings->value("ip").toString() : "";
}

void SettingsRepository::setConnectionPassword(QString password) {
    settings->setValue("password", password);
    settings->sync();
}

QString SettingsRepository::setConnectionPassword() {
    return settings->contains("password") ? settings->value("password").toString() : "";
}

void SettingsRepository::setConnectionUser(QString user) {
    settings->setValue("user",user);
    settings->sync();
}

QString SettingsRepository::getConnectionUser() {
    return settings->contains("user") ? settings->value("user").toString() : "";
}
