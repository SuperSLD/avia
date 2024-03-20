//
// Created by Леонид Соляной on 20.03.2024.
//

#include "Switcher.h"
#include "src/ui/common/widgets/button/Button.h"

#include <QHBoxLayout>

Switcher::Switcher(QString id, QList<QString> variants, QString selected) {
    this->selected = selected == nullptr ? variants.first() : selected;

    this->setMinimumHeight(54);
    coloredCardStyle(id, this, colorBlack(), 16, 0, 1, colorPrimary());
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    QHBoxLayout *variantsContainer = new QHBoxLayout;
    variantsContainer->setContentsMargins(0, 0, 0, 0);
    variantsContainer->setSpacing(0);
    this->setLayout(variantsContainer);

    int i = 0;
    foreach(QString variant, variants) {
        i++;
        switcherVariants.append(new SwitcherVariant(QString::number(i) + id, variant));
        variantsContainer->addWidget(switcherVariants.last());
        connect(switcherVariants.last(), &SwitcherVariant::onSelect, this, &Switcher::onVariantSelected);
        switcherVariants.last()->setSelected(variant == this->selected);
    }
}

Switcher::~Switcher() {
    foreach(SwitcherVariant *variant, switcherVariants) {
        delete variant;
    }
}

void Switcher::onVariantSelected(QString text) {
    this->selected = text;
    foreach(SwitcherVariant *variant, switcherVariants) {
        variant->setSelected(variant->getText() == this->selected);
    }
    emit onVariantSwitched(text);
}
