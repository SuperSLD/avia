//
// Created by Леонид Соляной on 20.03.2024.
//

#ifndef AVIA_SWITCHER_H
#define AVIA_SWITCHER_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "src/ui/common/widgets/switcher/SwitcherVariant.h"

#include <src/ui/theme/AppTheme.h>
using namespace theme;

class Switcher: public QWidget {
    Q_OBJECT

private:
    QString selected;
    QList<SwitcherVariant*> switcherVariants;

private slots:
    void onVariantSelected(QString text);

public:
    Switcher(QString id, QList<QString> variants, QString selected = nullptr);
    ~Switcher();

signals:
    void onVariantSwitched(QString text);
};

#endif //AVIA_SWITCHER_H
