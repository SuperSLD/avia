//
// Created by Леонид Соляной on 02.02.2024.
//

#include "FragmentFactoryImpl.h"
#include "src/ui/screens/splash/SplashFragment.h"
#include "src/ui/screens/main/MainFragment.h"
#include <QDebug>

using namespace screens;

FragmentFactoryImpl::FragmentFactoryImpl(){}
FragmentFactoryImpl::~FragmentFactoryImpl(){}

BaseFragment* FragmentFactoryImpl::create(QString tag) {
    qDebug() << "FragmentFactory: create - {" << tag << "}";
    if (tag == SPLASH_SCREEN) {
        return new SplashFragment;
    } else if (tag == MAIN_SCREEN) {
        return new MainFragment;
    } else {
        return nullptr;
    }
}

QString FragmentFactoryImpl::createStart() {
    return SPLASH_SCREEN;
}