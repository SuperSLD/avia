//
// Created by Леонид Соляной on 15.04.2024.
//

#include "PieChartWidget.h"
#include <QPainter>
#include <QPainterPath>

PieChartWidget::PieChartWidget(int h, QList<ChartLine> lines) {
    this->lines = lines;
    this->h = h;
}

PieChartWidget::~PieChartWidget() {

}

void PieChartWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    auto rect = QRect(this->width() / 2 - h / 2, this->height() / 2 - h / 2, h, h);
    auto data = lines.first();
    double sum = 0;
    foreach(double a, data.values) {
        sum += a;
    }
    auto degInOne = (360 + 5) / sum;
    auto currentDeg = 0;
    for (int i = 0; i < data.values.size(); i++) {
        QPainterPath path;
        path.moveTo(this->width()/2, this->height()/2);
        if (i == data.values.size() - 1) {
            path.arcTo(rect, 90, -data.values[i] * degInOne);
        } else {
            path.arcTo(rect, currentDeg + 90, data.values[i] * degInOne);
        }
        //painter.setPen(QPen(QColor(data.colors[i]), Qt::SolidPattern));
        painter.fillPath(path, QColor(data.colors[i]));
        currentDeg += data.values[i] * degInOne;
    }
}
