#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/ui/common/widgets/slidingstackedwidget/SlidingStackedWidget.h"
#include "src/ui/common/navigation/Router.h"
#include "src/data/settings/SettingsRepository.h"

Q_DECLARE_METATYPE(AnalyticsModel)
Q_DECLARE_METATYPE(QList<RouteModel*>)
Q_DECLARE_METATYPE(TransportGraphModel)
Q_DECLARE_METATYPE(Area)
Q_DECLARE_METATYPE(MetricsModel)

class MainWindow : public QMainWindow {
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
