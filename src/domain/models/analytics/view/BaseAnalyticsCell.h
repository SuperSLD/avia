//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_BASEANALYTICSCELL_H
#define AVIA_BASEANALYTICSCELL_H

#include <QString>
#include <QWidget>

/**
 * Базовая ячейка таблицы аналитики.
 *
 * Все классы ячеек таблицы аналитики наследуются от него.
 * Аналитические ячейки сохраняют в себе данные, необходимые
 * для отображения и реализуют функцию getView() для создания
 * виджета этой ячейки.
 */
class BaseAnalyticsCell {
public:
    BaseAnalyticsCell() {}

    /**
     * Метод, возвращающий виджет элемента
     * таблицы аналитики. Не принимает на вход никаких данных
     * и не выполняет сложных вычислений внутри себя.
     *
     * @return виджет, который будет отображаться
     *         в аналитической таблице.
     */
    virtual QWidget* getView() {};
};

#endif //AVIA_BASEANALYTICSCELL_H
