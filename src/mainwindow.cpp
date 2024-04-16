#include "mainwindow.h"
#include "src/ui/fragmentfactory/FragmentFactoryImpl.h"

#include <QDebug>
#include <QDesktopWidget>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    try {
        qDebug() << "App: create main window";

        qRegisterMetaType<AnalyticsModel>();
        qRegisterMetaType<QList<RouteModel*>>();

        settingsRepository = new SettingsRepository();

        container = new SlidingStackedWidget(this);
        container->setSpeed(500);
        container->setObjectName("ui");

        this->factory = new FragmentFactoryImpl;
        this->navigator = new Router(
                this->container,
                this->factory
        );

        connect(this->navigator, &Router::onThemeChanged, this, &MainWindow::onThemeChanged);

        setWindowBackColor();

        this->setWindowTitle("Avia");
        this->setWindowIcon(QIcon("/resc/splash.svg"));
        this->resize(QDesktopWidget().availableGeometry(this).size() * 0.95);
        this->setCentralWidget(container);
    } catch (std::exception& e) {
        qDebug("Application error");
        qDebug("%s", e.what());
    }
}

MainWindow::~MainWindow() {
    delete settingsRepository;
    delete container;
    delete navigator;
    delete factory;
}

void MainWindow::setWindowBackColor() {
    QString mainStyle = "QWidget#window {"
                        "   background-color:"+colorWhite()+";"
                        "}";
    container->setStyleSheet(mainStyle);
    container->setObjectName("window");
}

void MainWindow::onThemeChanged() {
    qDebug() << "MainWindow::onThemeChanged";
    setWindowBackColor();
}

