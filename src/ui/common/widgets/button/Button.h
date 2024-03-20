//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_BUTTON_H
#define AVIA_BUTTON_H


#include <QPushButton>

class Button: public QPushButton {
    Q_OBJECT

public:
    Button(QString id, QString title, bool solid = true);
    ~Button();
};


#endif //AVIA_BUTTON_H
