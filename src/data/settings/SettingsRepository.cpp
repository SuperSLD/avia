//
// Created by Леонид Соляной on 04.02.2024.
//

#include "SettingsRepository.h"

#include <QJsonDocument>
#include <QJsonObject>

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
    qDebug() << "setConnectionIp" << ip;
    settings->setValue("ip", ip);
    settings->sync();
}

QString SettingsRepository::getConnectionIp() {
    return settings->contains("ip") ? settings->value("ip").toString() : "";
}

void SettingsRepository::setConnectionPassword(QString password) {
    qDebug() << "setConnectionPassword" << password.size();
    settings->setValue("password", password);
    settings->sync();
}

QString SettingsRepository::setConnectionPassword() {
    return settings->contains("password") ? settings->value("password").toString() : "";
}

void SettingsRepository::setConnectionUser(QString user) {
    qDebug() << "setConnectionUser" << user;
    settings->setValue("user",user);
    settings->sync();
}

QString SettingsRepository::getConnectionUser() {
    return settings->contains("user") ? settings->value("user").toString() : "";
}

void SettingsRepository::setJson(QString key, QJsonObject json) {
    auto doc = QJsonDocument(json);
    auto str = QString(doc.toJson(QJsonDocument::Compact));
    settings->setValue(key,str);
    settings->sync();
}

QJsonObject SettingsRepository::getJson(QString key) {
    auto jsonString = settings->contains(key) ? settings->value(key).toString() : "";
    return QJsonDocument::fromJson(jsonString.toUtf8()).object();
}
