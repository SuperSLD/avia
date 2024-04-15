//
// Created by Леонид Соляной on 15.04.2024.
//

#include "ChartCellWidget.h"
#include "src/domain/models/analytics/view/chart/ChartLine.h"
#include "src/ui/common/widgets/analytictable/chart/pie/PieChartWidget.h"
#include "src/ui/common/widgets/analytictable/chart/bar/BarChartWidget.h"
#include "src/ui/common/widgets/analytictable/chart/line/LineChartWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QList>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

ChartCellWidget::ChartCellWidget(QString type, QString name, QList<ChartLine> lines) {
    auto *vContainer = new QVBoxLayout;
    vContainer->setSpacing(24);
    vContainer->setContentsMargins(24, 24, 24, 24);

    auto *nameLabel = new QLabel(name);
    textStyle("nameLabel", nameLabel, 20, colorBlack());
    nameLabel->setWordWrap(true);
    nameLabel->setAlignment(Qt::AlignLeft);
    nameLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    vContainer->addWidget(nameLabel);

    QFrame *chart;
    if (type == "pie") {
        chart = new PieChartWidget(400 - 10, lines);
    } else if (type == "line") {
        chart = new LineChartWidget(400 - 10, lines);
    } else if (type == "bar") {
        chart = new BarChartWidget(400 - 10, lines);
    } else {
        chart = new QFrame;
    }
    //coloredCardStyle("frame", chart, colorPrimary(), 0, 0);
    chart->setMinimumHeight(400);
    chart->setMaximumHeight(400);
    chart->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    vContainer->addWidget(chart);

    auto *labelsContainer = new QHBoxLayout;
    labelsContainer->setSpacing(16);
    labelsContainer->setAlignment(Qt::AlignLeft);
    if (type == "pie") {
        auto data = lines.first();
        for (int i = 0; i < data.values.size(); i++) {
            auto *partLabel = new QLabel( "▲ " + data.name[i] + " (" + QString::number(data.values[i]) + ")");
            textStyle("partLabel", partLabel, 16, data.colors[i]);
            labelsContainer->addWidget(partLabel);
        }
    } else {
        for (int i = 0; i < lines.size(); i++) {
            auto *partLabel = new QLabel( "▲ " + lines[i].name.first());
            textStyle("partLabel", partLabel, 16, lines[i].colors.first());
            labelsContainer->addWidget(partLabel);
        }
    }
    vContainer->addLayout(labelsContainer);

    coloredCardStyle("NumberCellWidget", this, colorWhite(), 24, 0, 1, colorBorder());
    this->setLayout(vContainer);
}

ChartCellWidget::~ChartCellWidget() {

}
