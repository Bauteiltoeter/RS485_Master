#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "busmaster.h"
#include "displayConnection.h"
#include "messagecontroller.h"
#include "display.h"
#include "contentmanager.h"
#include "slavemanager.h"

static QObject* messageController_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    MessageController tmp;
    return tmp.Instance();
}

static QObject* contentManager_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    ContentManager tmp;
    return tmp.Instance();
}

static QObject* connection_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return DisplayConnection::Instance();
}

static QObject* busmaster_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return Busmaster::Instance();
}

static QObject* slavemanager_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return SlaveManager::Instance();
}


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);



    QQmlApplicationEngine engine;


    qRegisterMetaType<size_t>("size_t");
   // qmlRegisterType<connection>("Displaymaster.connectionManager", 1, 0, "ConnectionManager");
    qmlRegisterType<Display>("Displaymaster.display", 1, 0, "Display");
    qmlRegisterType<SegmentDisplay>("Displaymanager.segment",1,0,"Segment");

    qmlRegisterSingletonType<DisplayConnection>("Displaymaster.connectionManager",1,0,"Con", connection_singletontype_provider);
    qmlRegisterSingletonType<Busmaster>("Displaymaster.Busmaster",1,0,"Busmaster", busmaster_singletontype_provider);
    qmlRegisterSingletonType<MessageController>("Displaymaster.messageController",1,0,"MessageController", messageController_singletontype_provider);
    qmlRegisterSingletonType<ContentManager>("Displaymaster.contentManager",1,0,"ContentManager", contentManager_singletontype_provider);
    qmlRegisterSingletonType<SlaveManager>("Displaymaster.SlaveManager",1,0,"SlaveManager", slavemanager_singletontype_provider);


    ContentManager::Instance()->setQmlEngine(&engine);
    SlaveManager::Instance()->setQmlEngine(&engine);


   // qmlRegisterType<MessageController>("Displaymaster.messageController", 1, 0, "MessageController");
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();




}
