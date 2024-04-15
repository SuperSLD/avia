//
// Created by Леонид Соляной on 15.04.2024.
//

#include "BarChartWidget.h"

#include <QPainter>
#include <QPainterPath>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

BarChartWidget::BarChartWidget(int h, QList<ChartLine> lines) {
    this->lines = lines;
    this->h = h;
}

BarChartWidget::~BarChartWidget() {

}

void BarChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    auto max = -1000000000.0;
    auto barsCount = 0;
    auto lineWithMaxBarCount = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (barsCount < lines[i].values.length()) {
            barsCount = lines[i].values.length();
            lineWithMaxBarCount = i;
        }
        for (int j = 0; j < lines[i].values.size(); j++) {
            if (max < lines[i].values[j]) {
                max = lines[i].values[j];
            }
        }
    }
    if (max > 10000) shortLabels = true;

    auto barWidth = this->width() * 0.5 / barsCount;
    auto barFirstSpace = 0;
    auto barSpace = this->width() * 0.5 / (barsCount + 1);
    auto barHeight = this->height() * 0.8;

    // лейблы баров
    painter.setFont(QFont("Roboto", 16, QFont::Normal));
    for (int i = 0; i < lines[lineWithMaxBarCount].values.size(); i++) {
        auto textRect = QRectF(
                barSpace * (i + 1) + barWidth * i,
                this->height() - 0.1 * this->height(),
                barWidth,
                this->height() * 0.1
        );
        painter.setPen(QPen(QColor(colorTextGray()), 3));
        painter.drawText(textRect, getLabel(lines[lineWithMaxBarCount].values[i]));
        painter.setPen(QPen(QColor(colorBorder()), 3));
        painter.drawLine(
                barSpace * (i + 1) + barWidth * i + 2,
                this->height() - 0.2 * this->height(),
                barSpace * (i + 1) + barWidth * i + 2,
                this->height() - 0.12 * this->height()
        );
    }

    // нижняя линия
    painter.setPen(QPen(QColor(colorBorder()), 3));
    painter.drawLine(
            0,
            this->height() - 0.2 * this->height(),
            this->width(),
            this->height() - 0.2 * this->height()
    );

    // пунктирные линии и значения
    auto lineCount = 5;
    for (int i = 0; i <= lineCount; i++) {
        auto textRect = QRectF(
                0,
                this->height() - 0.2 * this->height() - (this->height() * 0.8 / lineCount) * i + 2,
                barSpace + barFirstSpace,
                0.1 * this->height()
        );
        painter.setPen(QPen(QColor(colorTextGray()), 3));
        painter.drawText(textRect, getLabel(max / 5 * i));
        if (i != 0) {
            auto pen = QPen(QColor(colorBorder()), 2);
            pen.setDashPattern({4, 4});
            painter.setPen(pen);
            painter.drawLine(
                    0,
                    this->height() - 0.2 * this->height() - (this->height() * 0.8 / lineCount) * i + 2,
                    this->width(),
                    this->height() - 0.2 * this->height() - (this->height() * 0.8 / lineCount) * i + 2
            );
        }
    }

    // бары
    for (int i = 0; i < lines.size(); i++) {
        QPainterPath path;
        for (int j = 0; j < lines[i].values.size(); j++) {
            path.addRect(
                    barSpace * (j + 1) + barWidth * j,
                    this->height() - this->height() * 0.2,
                    barWidth,
                    - barHeight * (lines[i].values[j] / max)
            );
        }
        painter.fillPath(path, QColor(lines[i].colors.first()));
    }
}

QString BarChartWidget::getLabel(double val) {
    if (shortLabels) {
        return QString::number((int) (val / 1000)) + "K";
    } else {
        return QString::number((int) val);
    }
}

