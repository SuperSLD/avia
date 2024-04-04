//
// Created by Леонид Соляной on 18.03.2024.
//

#ifndef AVIA_SETTINGSTABFRAGMENT_H
#define AVIA_SETTINGSTABFRAGMENT_H


#include <QLabel>
#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/data/db/dbconnector/DBConnector.h"

class SettingsTabFragment: public BaseFragment {
    Q_OBJECT

private:
    SettingsRepository *settingsRep = new SettingsRepository();
    DBConnector* connector = nullptr;
    QLabel *ipLabel;
    QLabel *mongoLabel;

private slots:
    void onThemeSelected(QString theme);
    void onDatabaseChangeClicked();
    void onConnectionChecked(bool isConnected);

public:
    SettingsTabFragment();
    ~SettingsTabFragment();

    void onResume() override;

    void setConnector(DBConnector *connector) override;

signals:
    void onThemeSwitched();
    void onDatabaseChange();
};


#endif //AVIA_SETTINGSTABFRAGMENT_H
