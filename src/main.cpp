#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "connection.h"
#include "messagecontroller.h"

static QObject* example_qjsvalue_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);

    MessageController tmp;

    return tmp.Instance();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    qRegisterMetaType<size_t>("size_t");
    qmlRegisterType<connection>("Displaymaster.connectionManager", 1, 0, "ConnectionManager");

    qmlRegisterSingletonType<MessageController>("Displaymaster.messageController",1,0,"MessageController", example_qjsvalue_singletontype_provider);

   // qmlRegisterType<MessageController>("Displaymaster.messageController", 1, 0, "MessageController");
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
