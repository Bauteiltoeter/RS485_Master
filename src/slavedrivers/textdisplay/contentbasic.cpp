#include "contentbasic.h"
#include <QDebug>
#include <QQmlComponent>

ContentBasic::ContentBasic(int id, QQmlApplicationEngine* qmlEngine)
{
    contentID = id;
    this->qmlEngine = qmlEngine;

    gui= NULL;
}

QString ContentBasic::name()
{
    return "---";
}

void ContentBasic::run()
{
}

QString ContentBasic::headerText()
{
    return "";
}

QString ContentBasic::footerText()
{
    return "";
}

QObject *ContentBasic::mainWindow()
{
    return gui;
}

int ContentBasic::getContentID()
{
    return contentID;
}

void ContentBasic::activate()
{
    qDebug() << "Activated id: " << contentID;
    emit requestFocus(contentID);
}

void ContentBasic::createGUI(QString resource)
{
    QQmlComponent component(qmlEngine,QUrl(resource));

    gui = component.create();

}

