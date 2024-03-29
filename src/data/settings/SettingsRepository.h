//
// Created by Леонид Соляной on 04.02.2024.
//

#ifndef AVIA_SETTINGSREPOSITORY_H
#define AVIA_SETTINGSREPOSITORY_H

#include <qsettings.h>

class SettingsRepository {

private:
    QSettings *settings;

public:
    SettingsRepository();
    ~SettingsRepository();

    void setTheme(bool isLight);
    bool getTheme();

    void setConnectionIp(QString ip);
    QString getConnectionIp();

    void setConnectionPassword(QString password);
    QString setConnectionPassword();
};

#endif //AVIA_SETTINGSREPOSITORY_H
