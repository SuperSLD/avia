//
// Created by Леонид Соляной on 08.04.2024.
//

#ifndef AVIA_SWGBUTTON_H
#define AVIA_SWGBUTTON_H

#include <qpushbutton.h>

class SwgButton: public QPushButton {
Q_OBJECT

private:
    QString name;

    void selfClick();

public:
    SwgButton(QString path, QSize size, QString name = NULL);
    ~SwgButton();

signals:
    void onClicked(QString name);
};

#endif //AVIA_SWGBUTTON_H
