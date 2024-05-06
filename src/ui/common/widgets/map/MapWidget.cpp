//
// Created by Леонид Соляной on 16.04.2024.
//

#include "MapWidget.h"
#include "src/ui/common/widgets/swgbutton/SwgButton.h"
#include "src/ui/common/widgets/checkbox/CheckBox.h"

#include <QPainter>

#include <src/ui/theme/AppTheme.h>
#include <QPainterPath>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>

using namespace theme;

MapWidget::MapWidget() {
    country = new CountryShape("russia");
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

    // первый ряд кнопок управления
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

    auto *airportsBox = new CheckBox("Аэропорты", airportsVisible);
    buttonsCardContainer->addWidget(airportsBox);
    connect(airportsBox, &CheckBox::onChangeState, this, &MapWidget::onChangeAirportsVisible);

    auto *baseGraphBox = new CheckBox("Базовая сеть", baseGraphVisible);
    buttonsCardContainer->addWidget(baseGraphBox);
    connect(baseGraphBox, &CheckBox::onChangeState, this, &MapWidget::onChangeBaseGraphVisible);

    auto *areaBox = new CheckBox("Зоны доступности", areaVisible);
    buttonsCardContainer->addWidget(areaBox);
    connect(areaBox, &CheckBox::onChangeState, this, &MapWidget::onChangeAreaVisible);

    // инфо о зонах доступности
    areaCard = new QFrame();
    coloredCardStyle("areaCard", areaCard, colorWhite(), 16, 0, 1, colorBorder());
    buttonsContainer->addWidget(areaCard);
    areaCardContainer = new QHBoxLayout;
    areaCardContainer->setContentsMargins(16, 16, 16, 16);
    areaCardContainer->setSpacing(0);
    areaCard->setLayout(areaCardContainer);

}

MapWidget::~MapWidget() {
    delete country;
}

void MapWidget::setRoutes(QList<RouteModel*> routes) {
    this->routes = routes;
    repaint();
}

void MapWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawBack(&painter);
    if (areaVisible) {
        drawArea(&painter);
    }
    if (baseGraphVisible) {
        drawGraph(graph, &painter, colorBlack());
    }
    if (airportsVisible) {
        drawAirports(&painter);
    }
}


void MapWidget::drawBack(QPainter *painter) {
    // заливка
    foreach(auto region, country->regions) {
        QPainterPath path;
        for (int i = 0; i < region.size(); i++) {
            auto p = latLonToXY(region[i][1], region[i][0]);
            if (i == 0) {
                path.moveTo(p);
            } else {
                path.lineTo(p);
            }
        }
        painter->fillPath(path, QColor(colorBorder()));
    }
    // границы
    painter->setPen(QPen(QColor(colorGraySecondary()), 1));
    foreach(auto region, country->regions) {
        QPainterPath path;
        for (int i = 0; i < region.size(); i++) {
            auto p = latLonToXY(region[i][1], region[i][0]);
            if (i == 0) {
                path.moveTo(p);
            } else {
                path.lineTo(p);
            }
        }
        painter->drawPath(path);
    }
}

void MapWidget::drawArea(QPainter *painter) {
// зоны доступности
    QHash<int, QPainterPath> layers;
    for (int i = 0; i < colors.size(); i++) {
        layers[i] = QPainterPath();
    }
    foreach(auto line, area.points) {
        foreach(auto point, line) {
            auto colorIndex = (int) (point.distance / (double) area.maxDistance * (colors.size() - 1));
            auto p1 = latLonToXY(point.lat, point.lon);
            layers[colorIndex].addRect(
                    p1.x(),
                    p1.y(),
                    point.w * 5 * zoom,
                    point.h * 10 * zoom
            );
        }
    }
    foreach(auto ci, layers.keys()) {
        auto color = QColor(colors[ci]);
        color.setAlphaF(0.3);
        painter->fillPath(layers[ci], color);
    }
}

void MapWidget::drawAirports(QPainter *painter) {
    // аэропорты
    foreach(auto airport, graph.airports) {
        auto p = latLonToXY(airport.lat, airport.lon);
        if (p.x() >= 0 && p.x() <= this->width() && p.y() > 0 && p.y() < this->height()) {
            auto r = AIRPORT_POINT_SIZE_MIN + (AIRPORT_POINT_SIZE_MAX - AIRPORT_POINT_SIZE_MIN) *
                                              (airport.flightCount / (double) graph.maxAirportFlightCount);
            auto color = colors[(int) (airport.flightCount / (double) graph.maxAirportFlightCount * (colors.size() - 1))];
            QPainterPath path;
            path.addEllipse(p, r, r);
            painter->fillPath(path, QColor(color));
            if (zoom > 14) {
                painter->setPen(QPen(QColor(colorBlack()), 2));
                painter->setFont(QFont("Roboto", 16, QFont::Bold));
                painter->drawText(p.x() - r, p.y() + r * 3, airport.id);
                painter->setFont(QFont("Roboto", 12, QFont::Normal));
                painter->drawText(p.x() - r, p.y() + r * 3 + 16, airport.name);
                painter->drawText(p.x() - r, p.y() + r * 3 + 28, airport.city);
                painter->setPen(QPen(QColor(color), 2));
                painter->drawText(p.x() - r, p.y() + r * 3 + 40, "Пассажиров: " + QString::number(airport.passengersCountIn + airport.passengersCountOut));
                painter->drawText(p.x() - r, p.y() + r * 3 + 52, "Вылетов: " + QString::number(airport.flightCount));
            }
        }
    }
}


void MapWidget::drawGraph(TransportGraphModel graphForDraw, QPainter *painter, QString color) {
    painter->setPen(QColor(color));
    foreach(auto line, graphForDraw.viewLines) {
        auto p1 = latLonToXY(line[1], line[0]);
        auto p2 = latLonToXY(line[3], line[2]);
        painter->drawLine(p1, p2);
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
    qDebug() << "setArea maxTime" << area.maxTime;
    clearList(areaCardContainer);
    for (int i = 0; i < colors.size(); i++) {
        auto *colorCard = new QFrame();
        auto *colorContainer = new QVBoxLayout();
        colorContainer->setSpacing(8);
        colorContainer->setContentsMargins(0, 0, 0, 0);
        colorCard->setLayout(colorContainer);
        auto colorFrame = new QFrame();
        auto colorLabel = new QLabel(QString::number((int) (area.maxTime / colors.size() * (i + 1))) + "ч");
        colorContainer->addWidget(colorFrame);
        colorFrame->setMinimumSize(QSize(24, 24));
        coloredCardStyle("colorFrame", colorFrame, colors[i], 0, 0);
        colorContainer->addWidget(colorLabel);
        textStyle("colorLabel", colorLabel, 14, colorBlack());
        areaCardContainer->addWidget(colorCard);
    }
    this->area = area;
    repaint();
}

void MapWidget::onChangeAirportsVisible(bool checked) {
    airportsVisible = checked;
    repaint();
}

void MapWidget::onChangeAreaVisible(bool checked) {
    areaVisible = checked;
    repaint();
}

void MapWidget::onChangeBaseGraphVisible(bool checked) {
    baseGraphVisible = checked;
    repaint();
}

void MapWidget::clearList(QLayout *list) {
    QLayoutItem* child;
    while(list->count()!=0) {
        child = list->takeAt(0);
        if(child->layout() != 0) {
            clearList(child->layout());
        }
        else if(child->widget() != 0) {
            delete child->widget();
        }
        delete child;
    }
}
