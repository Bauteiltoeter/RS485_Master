#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "connection.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qRegisterMetaType<size_t>("size_t");
    qmlRegisterType<connection>("Displaymaster.connectionManager", 1, 0, "ConnectionManager");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
