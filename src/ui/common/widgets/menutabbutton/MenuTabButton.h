//
// Created by Леонид Соляной on 05.02.2024.
//

#ifndef AVIA_MENUTABBUTTON_H
#define AVIA_MENUTABBUTTON_H

#include <QPushButton>
#include "src/data/settings/SettingsRepository.h"

class MenuTabButton: public QPushButton {
    Q_OBJECT

private:
    int id;
    SettingsRepository settingsRep = SettingsRepository();

public:
    MenuTabButton(QString title, QString icon, QString iconDark, int id);
    ~MenuTabButton();

    void setSelected(int id);

private slots:
    void selfClick();

signals:
    void onClicked(int id);
};


#endif //AVIA_MENUTABBUTTON_H
