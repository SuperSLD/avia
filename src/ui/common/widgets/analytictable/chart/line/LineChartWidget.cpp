//
// Created by Леонид Соляной on 15.04.2024.
//

#include "LineChartWidget.h"

#include <QPainter>
#include <QDebug>
#include <QPainterPath>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

LineChartWidget::LineChartWidget(int h, QList<ChartLine> lines) {
    this->h = h;
    this->lines = lines;
}

LineChartWidget::~LineChartWidget() {

}

void LineChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    auto max = -1000000000.0;
    auto maxByX = -1000000000.0;
    auto pointCount = 0;
    auto lineWithMaxPointCount = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (pointCount < lines[i].values.length()) {
            pointCount = lines[i].values.length();
            lineWithMaxPointCount = i;
        }
        for (int j = 0; j < lines[i].values.size(); j++) {
            if (max < lines[i].values[j]) max = lines[i].values[j];
            if (maxByX < lines[i].valuesByX[j]) maxByX = lines[i].valuesByX[j];
        }
    }
    if (max > 10000) shortLabels = true;
    if (max > 1000000) shortShortLabels = true;
    if (maxByX > 10000) secondShortLabels = true;
    if (maxByX > 1000000) secondShortShortLabels = true;


    // лейблы значений
    painter.setFont(QFont("Roboto", 16, QFont::Normal));
    auto lineCount = 10;
    for (int i = 0; i <= lineCount; i++) {
        auto textRect = QRectF(
                this->width() / lineCount * i,
                this->height() - 0.1 * this->height(),
                this->width() / lineCount,
                this->height() * 0.1
        );
        painter.setPen(QPen(QColor(colorTextGray()), 3));
        if (i != lineCount) painter.drawText(textRect, getLabel(maxByX / lineCount * i,true));
        //painter.drawText(textRect, getLabel(i));
        painter.setPen(QPen(QColor(colorBorder()), 3));
        if (i != 0) {
            painter.drawLine(
                    this->width() / lineCount * i,
                    this->height() - 0.2 * this->height(),
                    this->width() / lineCount * i,
                    this->height() - 0.12 * this->height()
            );
            auto pen = QPen(QColor(colorBorder()), 2);
            pen.setDashPattern({4, 4});
            painter.setPen(pen);
            painter.drawLine(
                    this->width() / lineCount * i,
                    0,
                    this->width() / lineCount * i,
                    this->height() - 0.2 * this->height()
            );
        }
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
    lineCount = 5;
    for (int i = 0; i <= lineCount; i++) {
        auto textRect = QRectF(
                0,
                this->height() - 0.2 * this->height() - (this->height() * 0.8 / lineCount) * i + 2,
                50,
                0.1 * this->height()
        );
        painter.setPen(QPen(QColor(colorTextGray()), 3));
        painter.drawText(textRect, getLabel(max / lineCount * i));
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
            auto point = QPointF(
                    this->width() * (lines[i].valuesByX[j] / maxByX),
                    this->height() - 0.2 * this->height() - this->height() * 0.8 * lines[i].values[j] / max
            );
            if (j != 0) {
                path.lineTo(point);
            } else {
                path.moveTo(point);
            }
        }
        painter.setPen(QPen(QColor(lines[i].colors.first()), 3));
        painter.drawPath(path);
    }
}

QString LineChartWidget::getLabel(double val, bool isSecond) {
    if (shortLabels && !isSecond) {
        if (shortShortLabels) {
            return QString::number((int) (val / 1000000)) + "M";
        } else {
            return QString::number((int) (val / 1000)) + "K";
        }
    } else {
        if (secondShortLabels) {
            if (secondShortShortLabels) {
                return QString::number((int) (val / 1000000)) + "M";
            } else {
                return QString::number((int) (val / 1000)) + "K";
            }
        } else {
            return QString::number(val, 'f', 2);
        }
    }
}
