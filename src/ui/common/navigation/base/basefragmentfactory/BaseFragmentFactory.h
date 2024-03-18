//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_BASEFRAGMENTFACTORY_H
#define AVIA_BASEFRAGMENTFACTORY_H


#include "src/ui/common/navigation/base/basefragment/BaseFragment.h"

/**
 * @brief The BaseScreensFactory class
 *
 * Абстрактная фабрика экранов.
 */
class BaseFragmentFactory {
public:
    BaseFragmentFactory();
    ~BaseFragmentFactory();

    /**
     * @brief create
     * @param tag идентификатор экрана.
     *
     * Создание экрана по его
     * идентификатору для навигатора.
     * (фабрика инициализируетя при создании навигатора)
     *
     * @return BaseFragmnt.
     */
    virtual BaseFragment* create(QString tag);

    /**
     * @brief createStart
     *
     * Создание стартового окна прпиложения
     * для навигатора.
     *
     * @return стартовое окно приложения.
     */
    virtual QString createStart();

    //MainWindow *window;
};


#endif //AVIA_BASEFRAGMENTFACTORY_H
