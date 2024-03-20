//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_CHANGECONNECTIONFRAGMENT_H
#define AVIA_CHANGECONNECTIONFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/data/settings/SettingsRepository.h"
#include "src/ui/common/widgets/textedit/TextEdit.h"

class ChangeConnectionFragment: public BaseFragment {
    Q_OBJECT
private:
    SettingsRepository *settingsRep = new SettingsRepository();

    TextEdit *ipEdit;
    TextEdit *passwordEdit;

private slots:
    void onBack();
    void onSave();

public:
    ChangeConnectionFragment();
    ~ChangeConnectionFragment();
};


#endif //AVIA_CHANGECONNECTIONFRAGMENT_H
