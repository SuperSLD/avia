//
// Created by Леонид Соляной on 10.04.2024.
//

#ifndef AVIA_NUMBERANALYTICSCELL_H
#define AVIA_NUMBERANALYTICSCELL_H


#include <QString>
#include <QList>
#include "BaseAnalyticsCell.h"
#include "src/ui/common/widgets/analytictable/numbercell/NumberCellWidget.h"

/**
 * Ячейка аналитики с числом.
 */
class NumberAnalyticsCell: public BaseAnalyticsCell {

public:
    QString value;
    QString name;
    QString color;

    /**
     * Ячейка аналитики с одним значением.
     *
     * Когда использовать:
     * Использовать в случае, когда нужно отобразить одно
     * значение любого типа.
     *
     * Пример использования:
     * new NumberAnalyticsCell(mainTransportNode.id,"Главный транспортный узел", colorSecondary()),
     * new NumberAnalyticsCell(QString::number(viewLines.size()),"Количество связей", colorPrimary()),
     *
     * @param value значение, которое будет отображено
     *              большим шрифтом в центре ячейки.
     * @param name небольшой текст, который будет написан под
     *             значением.
     * @param color цвет текста value.
     */
    NumberAnalyticsCell(
        QString value,
        QString name,
        QString color
    ) {
        this->value = value;
        this->name = name;
        this->color = color;
    }

    NumberAnalyticsCell() {}

    QWidget* getView() override {
        return new NumberCellWidget(value, name, color);
    }
};


#endif //AVIA_NUMBERANALYTICSCELL_H
