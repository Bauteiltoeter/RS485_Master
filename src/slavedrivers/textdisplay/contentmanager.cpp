#include "contentmanager.h"
#include <QDebug>
#include <QQmlContext>
#include <QQuickItem>
#include <QQmlListProperty>
#include <QList>

#include "contentclock.h"
#include "contentFreetext.h"
#include "contentfinger.h"
#include "contentpowermeter.h"
#include "displayConnection.h"
#include "contentmonitoring.h"

ContentManager::ContentManager()
{
    contentPanel=NULL;

    currentFocus=-1;
}

ContentManager* ContentManager::Instance()
{
    static ContentManager* singleton = new ContentManager;
    return singleton;
}

void ContentManager::setQmlEngine(QQmlApplicationEngine *qmlEngine)
{
    this->qmlEngine = qmlEngine;

    contentList.append(new ContentClock(0,qmlEngine));
    contentList.append(new ContentFinger(1,qmlEngine));
    contentList.append(new ContentMonitoring(2,qmlEngine));
    contentList.append(new ContentFreetext(3,qmlEngine));
    contentList.append(new ContentPowermeter(4,qmlEngine));

    for(int i=0; i < contentList.size(); i++)
    {
        connect(contentList[i],SIGNAL(requestStringTransmit(int,QStringList)),this,SLOT(stringTransmitRequest(int,QStringList)));
        connect(contentList[i],SIGNAL(requestFocus(int)),this,SLOT(focusRequest(int)));
    }

    focusRequest(-1);
}

QList<QObject*> ContentManager::buttons()
{
    return buttonList;
}

QList<QObject *> ContentManager::mainWindows()
{
    return mainWindowList;
}

void ContentManager::visibleChanged(bool visible)
{
    static int oldFocus=-1;
    if(visible==false)
    {
        oldFocus = currentFocus;
        currentFocus=-1;
    }
    else
    {
        currentFocus = oldFocus;
    }
}

QString ContentManager::headerText()
{
    if(currentFocus>=0 && currentFocus<contentList.size())
        return contentList[currentFocus]->headerText();

    return "NIX";
}

QString ContentManager::footerText()
{
    if(currentFocus>=0 && currentFocus<contentList.size())
        return contentList[currentFocus]->footerText();
    return "NIX";
}

void ContentManager::focusRequest(int contentID)
{
    qDebug() << "focusRequest for id: " << contentID;
    for(int i=0; i < buttonList.size(); i++)
    {
        if(contentList[i]->getContentID()==contentID)
        {
            if(mainWindowList[i])
                mainWindowList[i]->setProperty("visible",true);
            buttonList[i]->setProperty("active",true);
        }
        else
        {
            if(mainWindowList[i])
            mainWindowList[i]->setProperty("visible",false);
            buttonList[i]->setProperty("active",false);
        }
    }
    currentFocus=contentID;
    emit headerTextChanged();
    emit footerTextChanged();
}

void ContentManager::stringTransmitRequest(int id, QStringList display)
{
    qDebug() << "StringTransmitRequest for id: " << id << ":\n" << display;

    if(id==currentFocus){
        DisplayConnection::Instance()->writeText(display);
    }
    else
    {
        qDebug() << "String transfer not permitted, not in focus";
    }
}

void ContentManager::load()
{

    QList<QObject*> rootObject = qmlEngine->rootObjects();//.first()->findChild<QQmlComponent*>("dynamicContentPanel");

    if(rootObject.empty())
        return;

    // contentPanel;
    contentPanel  = rootObject.first()->findChild<QQuickItem*>("dynamicConentPanel");


    qDebug() << "Found panel: " << contentPanel;

    static bool initialized=false;
    if(contentPanel && !initialized)
    {
        initialized=true;
        qDebug() << "ContentManager::buttons called";

        QQmlComponent component(qmlEngine,QUrl(QLatin1String("qrc:/qml/LCARSSiteButton.qml")));


        for(int i=0; i < contentList.size(); i++)
        {
            QObject *object = static_cast<QObject*>(component.create());

            object->setProperty("text",contentList[i]->name());
            object->setProperty("defaultWidth",200*194.89/229.969);
            connect(object,SIGNAL(clicked()),contentList[i],SLOT(activate()));
            buttonList.append(object);
            mainWindowList.append(contentList[i]->mainWindow());
        }
        emit buttonsChanged();
        emit mainWindowsChanged();
        start();

    }
}

void ContentManager::run()
{
    while(1)
    {
        msleep(100);

        if(currentFocus>=0 && currentFocus<contentList.size())
            contentList[currentFocus]->run();


    }
}
