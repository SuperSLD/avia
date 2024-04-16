//
// Created by Леонид Соляной on 16.04.2024.
//

#include "MapWidget.h"
#include "src/ui/common/widgets/swgbutton/SwgButton.h"

#include <QPainter>

#include <src/ui/theme/AppTheme.h>
#include <QPainterPath>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QMouseEvent>
#include <QVBoxLayout>

using namespace theme;

MapWidget::MapWidget() {
    QFile file;
    file.setFileName(":/resc/resc/russia.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    auto val = file.readAll();
    russia = QJsonDocument::fromJson(val);
    file.close();
    coloredCardStyle(
            "MapWidget",
            this,
            colorWhite(),
            0,
            0,
            0,
            nullptr,
            nullptr,
            nullptr,
            "   border-bottom-right-radius: 24px;"
            "   border-bottom-left-radius: 24px;");

    auto *buttonsFrame = new QFrame(this);
    auto *buttonsContainer = new QVBoxLayout;
    buttonsFrame->setLayout(buttonsContainer);
    buttonsContainer->setContentsMargins(24, 24, 24, 24);

    auto *buttonsCard = new QFrame();
    coloredCardStyle("buttonsCard", buttonsCard, colorWhite(), 16, 0, 1, colorBorder());
    buttonsContainer->addWidget(buttonsCard);
    auto *buttonsCardContainer = new QHBoxLayout;
    buttonsCardContainer->setContentsMargins(16, 16, 16, 16);
    buttonsCardContainer->setSpacing(16);
    buttonsCard->setLayout(buttonsCardContainer);

    auto *minusButton = new SwgButton("minus", QSize(36, 36), "minus");
    connect(minusButton, &SwgButton::onClicked, this, &MapWidget::onZoomChange);
    buttonsCardContainer->addWidget(minusButton);
    auto *plusButton = new SwgButton("plus", QSize(36, 36), "plus");
    connect(plusButton, &SwgButton::onClicked, this, &MapWidget::onZoomChange);
    buttonsCardContainer->addWidget(plusButton);
}

MapWidget::~MapWidget() {

}

void MapWidget::setRoutes(QList<RouteModel*> routes) {
    this->routes = routes;
    repaint();
}

void MapWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    // границы
    painter.setPen(QPen(QColor(colorBorder()), 1));
    foreach(auto region, russia.object()) {
        auto points = region.toObject()["0"].toArray();
        QPainterPath path;
        for(int i = 0; i < points.size(); i += 1) {
            auto p = latLonToXY(points[i].toArray()[0].toDouble(), points[i].toArray()[1].toDouble());
            if (i == 0) {
                path.moveTo(p);
            } else {
                path.lineTo(p);
            }
        }
        painter.drawPath(path);
    }

    // полеты
    painter.setPen(QPen(QColor(colorPrimary()), 2));
    for(int i = 0; i < routes.size(); i++) {
        QPainterPath path;
        auto points = routes[i]->data.list;
        if (points.size() > 0) {
            for(int j = 0; j < points.size(); j += 1) {
                auto p = latLonToXY(points[j].lat, points[j].lon);
                if (j == 0) {
                    path.moveTo(p);
                } else {
                    path.lineTo(p);
                }
            }
        }
        painter.drawPath(path);
    }
}

QPoint MapWidget::latLonToXY(double lat, double lon) {
    return QPoint(cameraX + (lon * 5) * zoom, cameraY + this->height() - (lat * 10) * zoom);
}

void MapWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isMove = true;
    } else if (event->button() == Qt::RightButton) {

    }
}

void MapWidget::mouseMoveEvent(QMouseEvent *event) {
    if (clickX < 0) {
        clickX = event->pos().x();
        clickY = event->pos().y();
    }
    cameraX = lastCameraX + event->pos().x() - clickX;
    cameraY = lastCameraY + event->pos().y() - clickY;
    repaint();
}

void MapWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isMove) {
        isMove = false;
        lastCameraX = cameraX;
        lastCameraY = cameraY;
        clickX = -1;
        clickY = -1;
        repaint();
    }
}

void MapWidget::onZoomChange(QString name) {
    double scaleFactor;
    if (name == "plus") {
        scaleFactor = 1.1;
    } else {
        scaleFactor = 0.9;
    }
    zoom *= scaleFactor;
    cameraX = cameraX * scaleFactor;
    cameraY = cameraY * scaleFactor;
    lastCameraX = cameraX;
    lastCameraY = cameraY;
    repaint();
}
