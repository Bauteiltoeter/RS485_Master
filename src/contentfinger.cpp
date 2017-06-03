#include "contentfinger.h"
#include <QQmlComponent>

ContentFinger::ContentFinger(int id, QQmlApplicationEngine* qmlEngine)
    : ContentBasic(id,qmlEngine)
{
    createGUI("qrc:/qml/ContentFinger.qml");
    connect(gui,SIGNAL(send()),this,SLOT(send()));

}

QString ContentFinger::name()
{

    return "Finger";
}

void ContentFinger::send()
{
    qDebug() << "ContentFinger::send activated";
    emit requestStringTransmit(contentID, QStringList() << "ROFL FINGER" << "HALLO WELT");
}
