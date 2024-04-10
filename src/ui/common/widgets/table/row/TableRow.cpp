//
// Created by Леонид Соляной on 08.04.2024.
//

#include <QHBoxLayout>
#include <QLabel>
#include "TableRow.h"
#include "src/ui/common/widgets/swgbutton/SwgButton.h"

#include <src/ui/theme/AppTheme.h>
#include <QSvgWidget>

using namespace theme;

TableRow::TableRow(BaseDBModel *model, bool isGray) {
    this->model = model;
    QHBoxLayout *container = new QHBoxLayout;
    container->setContentsMargins(16, 8, 16, 8);
    container->setSpacing(0);
    QHBoxLayout *preview = new QHBoxLayout;
    preview->setContentsMargins(0, 8, 0, 0);
    preview->setAlignment(Qt::AlignLeft);
    preview->setSpacing(8);
    QHBoxLayout *action = new QHBoxLayout;
    action->setContentsMargins(16, 8, 16, 8);
    action->setAlignment(Qt::AlignRight);
    container->setSpacing(0);

    container->addLayout(preview);
    container->addLayout(action);

    foreach(PreviewItem previewItem, model->getPreview()) {
        if (previewItem.type == "text") {
            QLabel *label = new QLabel(previewItem.value);
            textStyle("label", label, previewItem.size, previewItem.color, previewItem.isBold);
            label->setMinimumWidth(previewItem.width * 20);
            label->setMaximumWidth(previewItem.width * 20);
            preview->addWidget(label);
        }
        if (previewItem.type == "icon") {
            QSvgWidget *image = new QSvgWidget(":/resc/resc/" + previewItem.value + ".svg");
            squareWidgetStyle(image, 36);
            preview->addWidget(image);
        }
    }

    SwgButton *editButton = new SwgButton(
            settingsRep.getTheme() ? "edit" : "edit_dark",
            QSize(24, 24),
            "edit"
    );
    connect(editButton, &SwgButton::onClicked, this, &TableRow::onEditButtonClicked);
    action->addWidget(editButton);

    this->setLayout(container);
    if (isGray) {
        coloredCardStyle("row", this, colorGraySecondary(), 0, 0);
    } else {
        coloredCardStyle("row", this, colorWhite(), 0, 0);
    }
}

TableRow::~TableRow() {
    delete model;
}

void TableRow::onEditButtonClicked(QString name) {
    emit onModelOpen(model);
}
