#include "src/mainwindow.h"

#include <QApplication>
#include <mongocxx/instance.hpp>

int main(int argc, char *argv[])
{
    mongocxx::instance instance{};
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
