//
// Created by Леонид Соляной on 10.04.2024.
//

#include <QLabel>
#include "ModelDetailFragment.h"
#include "src/ui/common/widgets/button/Button.h"
#include "src/data/db/dbconnector/models/basedbmodel/BaseDBModel.h"

#include <src/ui/theme/AppTheme.h>
#include <QScrollArea>
#include <QScrollArea>
#include <QScrollBar>
#include <QSvgWidget>

using namespace theme;

ModelDetailFragment::ModelDetailFragment() {
    QHBoxLayout *hContainer = new QHBoxLayout;
    hContainer->setContentsMargins(24, 24, 24, 24);
    QVBoxLayout *vContainer = new QVBoxLayout;
    hContainer->setAlignment(Qt::AlignHCenter);
    hContainer->addLayout(vContainer);
    vContainer->setAlignment(Qt::AlignVCenter);

    headerContainer = new QHBoxLayout;
    headerContainer->setAlignment(Qt::AlignLeft);
    QLabel *titleLabel = new QLabel("Просмотр записи");
    titleLabel->setMinimumWidth(650);
    textStyle("titleLabel", titleLabel, 24, colorBlack(), true);
    vContainer->addWidget(titleLabel);
    vContainer->addLayout(headerContainer);

    // зона прокрутки
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setMinimumWidth(900);
    scrollArea->setMaximumWidth(900);
    QWidget *scrolContainer = new QWidget;
    scrollBar("scrollArea", scrollArea);
    QHBoxLayout *deskContainer = new QHBoxLayout;
    rowsContainer = new QVBoxLayout;
    rowsContainer->setSpacing(0);
    rowsContainer->setAlignment(Qt::AlignTop);
    deskContainer->addLayout(rowsContainer);
    deskContainer->setContentsMargins(0, 0, 0, 0);
    rowsContainer->setContentsMargins(0,0,0,0);
    scrolContainer->setLayout(deskContainer);
    scrollArea->setWidget(scrolContainer);
    scrollArea->setWidgetResizable(true);
    scrollArea->horizontalScrollBar()->setEnabled(false);
    scrollArea->verticalScrollBar()->hide();
    scrollArea->verticalScrollBar()->setMaximumWidth(0);
    vContainer->addWidget(scrollArea);

    QHBoxLayout *buttonContainer = new QHBoxLayout;
    buttonContainer->setAlignment(Qt::AlignRight);
    buttonContainer->setContentsMargins(0, 0, 0, 0);
    vContainer->addLayout(buttonContainer);

    Button *backButton = new Button("backButton", "Назад", false);
    buttonContainer->addWidget(backButton);
    connect(backButton, &Button::clicked, this, &ModelDetailFragment::onBack);

    coloredCardStyle("ChangeConnectionFragment", this, colorWhite(), 0, 0, 0);
    this->setLayout(hContainer);
}

ModelDetailFragment::~ModelDetailFragment() {
    delete settingsRep;
    delete rowsContainer;
}

void ModelDetailFragment::onBack() {
    emit back();
}

void ModelDetailFragment::onEdit() {

}

void ModelDetailFragment::bindData(BaseModel *model) {
    dbModel = dynamic_cast<BaseDBModel*>(model);
    foreach(PreviewItem previewItem, dbModel->getPreview()) {
        if (previewItem.type == "text") {
            QLabel *label = new QLabel(previewItem.value);
            textStyle("label", label, previewItem.size, previewItem.color, previewItem.isBold);
            label->setMinimumWidth(previewItem.width * 20);
            label->setMaximumWidth(previewItem.width * 20);
            headerContainer->addWidget(label);
        }
        if (previewItem.type == "icon") {
            QSvgWidget *image = new QSvgWidget(":/resc/resc/" + previewItem.value + ".svg");
            squareWidgetStyle(image, 36);
            headerContainer->addWidget(image);
        }
    }
    headerContainer->update();
    foreach(DetailItem detailLine, dbModel->getDetail()) {
        auto lineFrame = new QFrame;
        coloredCardStyle("lineFrame", lineFrame, colorGraySecondary(), 0, 0);
        auto *hContainer = new QHBoxLayout;
        lineFrame->setLayout(hContainer);
        hContainer->setContentsMargins(16, 16, 16, 16);
        hContainer->setSpacing(16);
        auto *nameLabel = new QLabel(detailLine.paramName);
        textStyle("nameLabel", nameLabel, 18, colorPrimary(), true);
        auto *descriptionLabel = new QLabel(detailLine.paramDescription);
        textStyle("descriptionLabel", descriptionLabel, 18, colorBlack());
        auto *valueLabel = new QLabel(detailLine.paramValue);
        textStyle("valueLabel", valueLabel, 18, colorBlack(), true);
        hContainer->addWidget(nameLabel);
        hContainer->addWidget(descriptionLabel);
        hContainer->addWidget(valueLabel);
        rowsContainer->addWidget(lineFrame);
    }
}
