#include "mainwindow.h"
#include "src/ui/fragmentfactory/FragmentFactoryImpl.h"

#include <QDebug>
#include <QDesktopWidget>

#include <src/ui/theme/AppTheme.h>
using namespace theme;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    try {
        qDebug() << "App: create main window";

        settingsRepository = new SettingsRepository();
        settingsRepository->setTheme(true);

        container = new SlidingStackedWidget(this);
        container->setSpeed(500);
        container->setObjectName("ui");

        this->factory = new FragmentFactoryImpl;
        this->navigator = new Router(
                this->container,
                this->factory
        );

        QString mainStyle = "QWidget#window {"
                            "   background-color:"+colorWhite()+";"
                            "}";
        container->setStyleSheet(mainStyle);
        container->setObjectName("window");

        this->setWindowTitle("Avia");
        this->setWindowIcon(QIcon("/resc/splash.svg"));
        this->resize(QDesktopWidget().availableGeometry(this).size() * 0.95);
        this->setCentralWidget(container);
    } catch (std::exception& e) {
        qDebug("%s", e.what());
    }
}

MainWindow::~MainWindow() {
    delete settingsRepository;
    delete container;
    delete navigator;
    delete factory;
}

