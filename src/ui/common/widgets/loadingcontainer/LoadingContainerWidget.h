//
// Created by Леонид Соляной on 03.04.2024.
//

#ifndef AVIA_LOADINGCONTAINERWIDGET_H
#define AVIA_LOADINGCONTAINERWIDGET_H

#include <QFrame>
#include <QStackedWidget>
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>
#include "src/ui/common/widgets/waitingspinner/WaitingSpinnerWidget.h"

/**
 * @brief The LoadingContainerWidget class
 *
 * Контейнер для отображения лоадеров.
 * Скрывает часть экрана и заменяет ее кружком
 * с загрузкой.
 *
 */
class LoadingContainerWidget : public QFrame {
Q_OBJECT

private:
    QString message;
    QStackedWidget *stack;
    QLabel *loadingLable;
    QLabel *errorLable;
    WaitingSpinnerWidget *loader;

public:
    LoadingContainerWidget(QFrame *content);
    ~LoadingContainerWidget();

    /**
     * @brief showLoading
     *
     * Отображение загрузки.
     *
     * @param message сообщение, которое увидит пользователь.
     */
    void startLoading(QString message = "Загрузка...");

    /**
     * @brief stopLoading
     *
     * Завершение загрузки, и отображение
     * основного контента.
     *
     */
    void stopLoading();

    /**
     * @brief error
     *
     * Отображение состояния ошибки.
     *
     * @param message текст ошибки.
     */
    void error(QString message = "Ошибка");
};

#endif //AVIA_LOADINGCONTAINERWIDGET_H
