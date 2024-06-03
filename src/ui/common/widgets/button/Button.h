//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_BUTTON_H
#define AVIA_BUTTON_H


#include <QPushButton>
#include <QLabel>

class Button: public QPushButton {
    Q_OBJECT

private:
    bool isEnabled = true;
    bool solid;
    QString id;
    QLabel *titleLabel;

public:
    Button(QString id, QString title, bool solid = true);
    ~Button();

    void enabled(bool isEnabled);
};


#endif //AVIA_BUTTON_H
