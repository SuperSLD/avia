//
// Created by Леонид Соляной on 02.02.2024.
//

#ifndef AVIA_BASEMODEL_H
#define AVIA_BASEMODEL_H


/**
 * @brief The BaseModel class
 *
 * Базовая модель объекта,
 * от которого наследуются все
 * другие объекты, передающиеся
 * между экранами.
 *
 */
class BaseModel {

public:
    BaseModel();
    virtual void pol();
};


#endif //AVIA_BASEMODEL_H
