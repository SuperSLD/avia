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
    file.setFileName(":/resc/resc/jsondata/russia.json");
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

    // заливка
    foreach(auto region, russia.object()) {
        auto points = region.toObject()["0"].toArray();
        QPainterPath path;
        for (int i = 0; i < points.size(); i++) {
            auto p = latLonToXY(points[i].toArray()[0].toDouble(), points[i].toArray()[1].toDouble());
            if (i == 0) {
                path.moveTo(p);
            } else {
                path.lineTo(p);
            }
        }
        painter.fillPath(path, QColor(colorBorder()));
    }
    // границы
    painter.setPen(QPen(QColor(colorGraySecondary()), 1));
            foreach(auto region, russia.object()) {
            auto points = region.toObject()["0"].toArray();
            QPainterPath path;
            for (int i = 0; i < points.size(); i++) {
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

    // зоны доступности
    foreach(auto line, area.points) {
        foreach(auto point, line) {
                QPainterPath path;
                auto p1 = latLonToXY(point.lat, point.lon);
                path.addRect(p1.x(), p1.y(), point.w * 5 * zoom + 1, point.h * 10 * zoom + 1);
                auto color = QColor(colors[(int) (point.distance / (double) area.maxDistance * (colors.size() - 1))]);
                color.setAlphaF(0.3);
                painter.fillPath(path, color);
        }
    }

    // аэропорты
    foreach(auto airport, graph.airports) {
        auto p = latLonToXY(airport.lat, airport.lon);
        if (p.x() >= 0 && p.x() <= this->width() && p.y() > 0 && p.y() < this->height()) {
            auto r = AIRPORT_POINT_SIZE_MIN + (AIRPORT_POINT_SIZE_MAX - AIRPORT_POINT_SIZE_MIN) *
                                              (airport.flightCount / (double) graph.maxAirportFlightCount);
            auto color = colors[(int) (airport.flightCount / (double) graph.maxAirportFlightCount * (colors.size() - 1))];
            QPainterPath path;
            path.addEllipse(p, r, r);
            painter.fillPath(path, QColor(color));
            if (zoom > 14) {
                painter.setPen(QPen(QColor(colorBlack()), 2));
                painter.setFont(QFont("Roboto", 16, QFont::Bold));
                painter.drawText(p.x() - r, p.y() + r * 3, airport.id);
                painter.setFont(QFont("Roboto", 12, QFont::Normal));
                painter.drawText(p.x() - r, p.y() + r * 3 + 16, airport.name);
                painter.drawText(p.x() - r, p.y() + r * 3 + 28, airport.city);
                painter.setPen(QPen(QColor(color), 2));
                painter.drawText(p.x() - r, p.y() + r * 3 + 40, "Пассажиров: " + QString::number(airport.passengersCountIn + airport.passengersCountOut));
                painter.drawText(p.x() - r, p.y() + r * 3 + 52, "Вылетов: " + QString::number(airport.flightCount));
            }
        }
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
    int k = 0;
    if (name == "plus") {
        scaleFactor = 1.1;
        k = +1;
    } else {
        scaleFactor = 0.9;
        k = -1;
    }
    zoom *= scaleFactor;
    qDebug() << "zoom =" << zoom;
    cameraX = cameraX * scaleFactor;// + (this->width() / 2) * scaleFactor * k;
    cameraY = cameraY * scaleFactor;// + (this->height() / 2) * scaleFactor * k;
    lastCameraX = cameraX;
    lastCameraY = cameraY;
    repaint();
}

void MapWidget::setAirports(TransportGraphModel graph) {
    this->graph = graph;
    repaint();
}

void MapWidget::setArea(Area area) {
    this->area = area;
    repaint();
}
