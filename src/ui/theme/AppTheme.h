//
// Created by Леонид Соляной on 04.02.2024.
//

#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QWidget>
#include "src/data/settings/SettingsRepository.h"

namespace theme {

    static SettingsRepository settingsRep = SettingsRepository();

    static const QString _COLOR_PRIMARY = "#80C693";
    static const QString _COLOR_SECONDARY = "#B9AAFF";
    static const QString _COLOR_BLACK = "#1C1C1C";
    static const QString _COLOR_WHITE = "#FFFFFF";
    static const QString _COLOR_WHITE_TEXT = "#FFFFFF";
    static const QString _COLOR_GRAY = "#F0F0F6";
    static const QString _COLOR_BORDER = "#F0F0F6";
    static const QString _COLOR_TEXT_GRAY = "#C7C9D8";
    static const QString _COLOR_TEXT_PRIMARY = "#C6E5CE";
    static const QString _COLOR_GRAY_SECONDARY = "#FAFBFC";
    static const QString _COLOR_RED = "#FF7474";
    static const QColor  _COLOR_PRIMARY_QT = QColor(128, 198, 147);

    static const QString _DARK_COLOR_PRIMARY = "#80C693";
    static const QString _DARK_COLOR_SECONDARY = "#B9AAFF";
    static const QString _DARK_COLOR_BLACK = "#FFFFFF";
    static const QString _DARK_COLOR_WHITE = "#33363A";
    static const QString _DARK_COLOR_WHITE_TEXT = "#FFFFFF";
    static const QString _DARK_COLOR_GRAY = "#2D2D32";
    static const QString _DARK_COLOR_BORDER = "#50515A";
    static const QString _DARK_COLOR_TEXT_GRAY = "#C7C9D8";
    static const QString _DARK_COLOR_TEXT_PRIMARY = "#C6E5CE";
    static const QString _DARK_COLOR_GRAY_SECONDARY = "#383C40";
    static const QString _DARK_COLOR_RED = "#FF7474";
    static const QColor  _DARK_COLOR_PRIMARY_QT = QColor(128, 198, 147);

    static const QList<QString> colors = QList<QString> {
            "#88C78C",
            "#9DC878",
            "#AFC866",
            "#C2C952",
            "#D7CA3E",
            "#E9CB2C",
            "#FCCC19",
            "#FFC216",
            "#FFB716",
            "#FFAB16",
            "#FF9316",
            "#FF8816",
            "#FF8816",
            "#FF7E16",
    };

    static QString colorPrimary() {
        return settingsRep.getTheme() ? _COLOR_PRIMARY : _DARK_COLOR_PRIMARY;
    }

    static QString colorSecondary() {
        return settingsRep.getTheme() ? _COLOR_SECONDARY : _DARK_COLOR_SECONDARY;
    }

    static QString colorBlack() {
        return settingsRep.getTheme() ? _COLOR_BLACK : _DARK_COLOR_BLACK;
    }

    static QString colorWhite() {
        return settingsRep.getTheme() ? _COLOR_WHITE : _DARK_COLOR_WHITE;
    }

    static QString colorWhiteText() {
        return settingsRep.getTheme() ? _COLOR_WHITE_TEXT : _DARK_COLOR_WHITE_TEXT;
    }

    static QString colorGray() {
        return settingsRep.getTheme() ? _COLOR_GRAY : _DARK_COLOR_GRAY;
    }

    static QString colorBorder() {
        return settingsRep.getTheme() ? _COLOR_BORDER : _DARK_COLOR_BORDER;
    }

    static QString colorTextGray() {
        return settingsRep.getTheme() ? _COLOR_TEXT_GRAY : _DARK_COLOR_TEXT_GRAY;
    }

    static QString colorTextPrimary() {
        return settingsRep.getTheme() ? _COLOR_TEXT_PRIMARY : _DARK_COLOR_TEXT_PRIMARY;
    }

    static QString colorGraySecondary() {
        return settingsRep.getTheme() ? _COLOR_GRAY_SECONDARY : _DARK_COLOR_GRAY_SECONDARY;
    }

    static QString colorRed() {
        return settingsRep.getTheme() ? _COLOR_RED : _DARK_COLOR_RED;
    }

    static QColor colorPrimaryQt() {
        return settingsRep.getTheme() ? _COLOR_PRIMARY_QT : _DARK_COLOR_PRIMARY_QT;
    }

    static void squareWidgetStyle(QWidget *widget, int size) {
        widget->setMinimumSize(QSize(size, size));
        widget->setMaximumSize(QSize(size, size));
    }

    static void whiteCardStyle(QString name, QWidget *widget, int padding = 24, int borderRadius = 24) {
        widget->setObjectName(name);
        widget->setStyleSheet(
                "QWidget#"+name+" {"
                "   background-color:"+colorWhite()+";"
                "   border-radius: "+QString::number(borderRadius)+"px;"
                "   padding: "+QString::number(padding)+"px;"
                "}"
        );
    }

    static void coloredCardStyle(
            QString name,
            QWidget *widget,
            QString color = colorWhite(),
            int corners = 24,
            int padding = 24,
            int border = 0,
            QString borderColor = nullptr,
            QString hoverColor = nullptr,
            QString hoverBorderColor = nullptr,
            QString other = ""
    ) {
        borderColor = (borderColor == nullptr) ? color : borderColor;
        widget->setObjectName(name);
        if (hoverBorderColor != nullptr && hoverColor != nullptr) {
            widget->setStyleSheet(
                    "QWidget#"+name+" {"
                    "   background-color:"+color+";"
                    "   border-radius: "+QString::number(corners)+"px;"
                    "   padding: "+QString::number(padding)+"px;"
                    "   border:"+ QString::number(border) +"px solid " + borderColor + ";"
                    "" + other + ""
                    "}"
                    "QWidget#"+name+":hover {"
                    "   background-color:"+hoverColor+";"
                    "   border:"+ QString::number(border) +"px solid " + hoverBorderColor+ ";"
                    "" + other + ""
                    "}"
            );
        } else {
            widget->setStyleSheet(
                    "QWidget#"+name+" {"
                    "   background-color:"+color+";"
                    "   border-radius: "+QString::number(corners)+"px;"
                    "   padding: "+QString::number(padding)+"px;"
                    "   border:"+ QString::number(border) +"px solid " + borderColor + ";"
                    "" + other + ""
                    "}"
            );
        }
    }

    static void textStyle(
            QString name,
            QWidget *widget,
            int size = 20,
            QString color = colorBlack(),
            bool isBold = false
    ) {
        widget->setObjectName(name);
        int weight = isBold ? QFont::Bold : QFont::Normal;
        widget->setFont(QFont("Roboto", size, weight));
        widget->setStyleSheet(
                "QWidget#"+name+" {"
                "   color: "+color+";"
                "}"
        );
    }

    static void scrollBar(
        QString name,
        QWidget *widget,
        int bottomRadius = 24
    ) {
        widget->setObjectName(name);
        widget->setStyleSheet(
            "QWidget#"+name+" {"
            "   background-color:"+colorWhite()+";"
            "   border-bottom-right-radius: "+QString::number(bottomRadius)+"px;"
            "   border-bottom-left-radius: "+QString::number(bottomRadius)+"px;"
            "}"
            "QScrollBar:vertical {"
            "   border: 0px solid "+colorWhite()+";"//COLOR_BORDER+";"
            "   background-color: "+colorWhite()+";"
            "   width: 0px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar:horizontal {"
            "   border: 0px solid "+colorWhite()+";"//COLOR_BORDER+";"
            "   background-color: "+colorWhite()+";"
            "   height: 0px;"
            "   margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle {"
            "   background-color: "+colorWhite()+";"//COLOR_TEXT_HINT+";"
            "   border: 3px solid "+colorWhite()+";"
            "   border-radius: 6px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "   height: 0px;"
            "   subcontrol-position: bottom;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical {"
            "   height: 0 px;"
            "   subcontrol-position: top;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::add-line:horizontal {"
            "   width: 0px;"
            "   subcontrol-position: right;"
            "   subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:horizontal {"
            "   width: 0 px;"
            "   subcontrol-position: left;"
            "   subcontrol-origin: margin;"
            "}"
        );
    }
}

#endif //THEME_H
