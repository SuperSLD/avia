#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/ui/common/widgets/slidingstackedwidget/SlidingStackedWidget.h"
#include "src/ui/common/navigation/Router.h"
#include "src/data/settings/SettingsRepository.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
    SettingsRepository *settingsRepository;

    SlidingStackedWidget *container;
    Router *navigator;
    BaseFragmentFactory *factory;

private slots:
    void onThemeChanged();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setWindowBackColor();
};
#endif // MAINWINDOW_H
