//
// Created by Леонид Соляной on 18.03.2024.
//

#ifndef AVIA_SETTINGSTABFRAGMENT_H
#define AVIA_SETTINGSTABFRAGMENT_H


#include <QLabel>
#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/data/settings/SettingsRepository.h"

class SettingsTabFragment: public BaseFragment {
    Q_OBJECT

private:
    SettingsRepository *settingsRep = new SettingsRepository();

    QLabel *ipLabel;

private slots:
    void onThemeSelected(QString theme);
    void onDatabaseChangeClicked();
public:
    SettingsTabFragment();
    ~SettingsTabFragment();

    void onResume() override;

signals:
    void onThemeSwitched();
    void onDatabaseChange();
};


#endif //AVIA_SETTINGSTABFRAGMENT_H
