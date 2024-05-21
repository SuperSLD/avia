//
// Created by Леонид Соляной on 06.05.2024.
//

#ifndef AVIA_BASEANALYTICMODEL_H
#define AVIA_BASEANALYTICMODEL_H

#include "src/ui/common/navigation/base/basemodel/BaseModel.h"
#include "src/domain/models/analytics/view/AnalyticsRow.h"

/**
 * Базовая модель с данными, которые можно отображать в таблице.
 *
 * Эти классы должны реализовывать в себе метод getRows()
 * чтобы их можно было отображать в AnalyticsTable.
 */
class BaseAnalyticModel: public BaseModel {

public:
    BaseAnalyticModel() {};
    ~BaseAnalyticModel() {};

    /**
     * Функция, которая возвращает сформированные
     * для отображения в AnalyticsTable данные.
     *
     * @param isSingle параметр отвечающий за отступ под данными.
     *                 если isSingle=true то добавляем списку строк EmptyAnalyticsCell.
     *                 (isSingle=true на отдельных экранах, isSingle=false на
     *                 общем экране с аналитикой)
     * @return список строк для отображения данных.
     */
    virtual QList<AnalyticsRow> getRows(bool isSingle = true) { return QList<AnalyticsRow>(); };
};

#endif //AVIA_BASEANALYTICMODEL_H
