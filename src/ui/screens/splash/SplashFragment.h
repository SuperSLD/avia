//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_SPLASHFRAGMENT_H
#define AVIA_SPLASHFRAGMENT_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"
#include "src/data/settings/SettingsRepository.h"

class SplashFragment: public BaseFragment {
    Q_OBJECT
private:
    SettingsRepository *settingsRepository;

public:
    SplashFragment();
    ~SplashFragment();

public slots:

    /**
     * @brief openStartScreen
     *
     * Переходим к меню после небольшой
     * задержки, чтобы юзверь успел увидеть
     * лого игры.
     */
    void openStartScreen();
};



#endif //AVIA_SPLASHFRAGMENT_H
