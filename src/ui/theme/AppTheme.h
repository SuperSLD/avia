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
    static const QString _COLOR_TEXT_GRAY = "#C7C9D8";
    static const QString _COLOR_TEXT_PRIMARY = "#C6E5CE";
    static const QString _COLOR_GRAY_SECONDARY = "#FAFBFC";
    static const QString _COLOR_RED = "#FF7474";

    static const QString _DARK_COLOR_PRIMARY = "#80C693";
    static const QString _DARK_COLOR_SECONDARY = "#B9AAFF";
    static const QString _DARK_COLOR_BLACK = "#FFFFFF";
    static const QString _DARK_COLOR_WHITE = "#33363A";
    static const QString _DARK_COLOR_WHITE_TEXT = "#FFFFFF";
    static const QString _DARK_COLOR_GRAY = "#2D2D32";
    static const QString _DARK_COLOR_TEXT_GRAY = "#C7C9D8";
    static const QString _DARK_COLOR_TEXT_PRIMARY = "#C6E5CE";
    static const QString _DARK_COLOR_GRAY_SECONDARY = "#FAFBFC";
    static const QString _DARK_COLOR_RED = "#FF7474";

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

    static QString colorTextGray() {
        return settingsRep.getTheme() ? _COLOR_TEXT_GRAY : _DARK_COLOR_TEXT_GRAY;
    }

    static QString colorTextPrimary() {
        return settingsRep.getTheme() ? _COLOR_TEXT_PRIMARY : _DARK_COLOR_TEXT_PRIMARY;
    }

    static QString colorGraySecondary() {
        return settingsRep.getTheme() ? _COLOR_GRAY_SECONDARY : _DARK_COLOR_GRAY_SECONDARY;
    }

    static QString colorRes() {
        return settingsRep.getTheme() ? _COLOR_RED : _DARK_COLOR_RED;
    }

    static void squareWidgetStyle(QWidget *widget, int size) {
        widget->setMinimumSize(QSize(size, size));
        widget->setMaximumSize(QSize(size, size));
    }

    static void whiteCardStyle(QString name, QWidget *widget) {
        widget->setObjectName(name);
        widget->setStyleSheet(
                "QWidget#"+name+" {"
                "   background-color:"+colorWhite()+";"
                "   border-radius: 24px;"
                "   padding: 24px;"
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
            QString hoverBorderColor = nullptr
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
                    "}"
                    "QWidget#"+name+":hover {"
                    "   background-color:"+hoverColor+";"
                    "   border:"+ QString::number(border) +"px solid " + hoverBorderColor+ ";"
                    "}"
            );
        } else {
            widget->setStyleSheet(
                    "QWidget#"+name+" {"
                    "   background-color:"+color+";"
                    "   border-radius: "+QString::number(corners)+"px;"
                    "   padding: "+QString::number(padding)+"px;"
                    "   border:"+ QString::number(border) +"px solid " + borderColor + ";"
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
}

#endif //THEME_H
