//
// Created by Леонид Соляной on 02.02.2024.
//

#include "SplashFragment.h"
#include <QSvgWidget>
#include <QTimer>

#include "src/ui/fragmentfactory/FragmentFactoryImpl.h"
using namespace screens;

SplashFragment::SplashFragment() {

    settingsRepository = new SettingsRepository();

    QVBoxLayout *mainVLayout = new QVBoxLayout;
    QHBoxLayout *mainHLayout = new QHBoxLayout;
    QSvgWidget *centerConainer = new QSvgWidget(
            settingsRepository->getTheme() ? ":/resc/resc/splash.svg" : ":/resc/resc/splash_dark.svg"
    );

    mainHLayout->addWidget(centerConainer);
    mainHLayout->setAlignment(Qt::AlignCenter);
    mainVLayout->addLayout(mainHLayout);
    mainVLayout->setAlignment(Qt::AlignCenter);

    this->setLayout(mainVLayout);

    QTimer::singleShot(1000, this, SLOT(openStartScreen()));
}

SplashFragment::~SplashFragment() {
    delete settingsRepository;
}

void SplashFragment::openStartScreen() {
    emit newRootScreen( MAIN_SCREEN);
}
