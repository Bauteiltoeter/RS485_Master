#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QThread>
#include "contentbasic.h"

class ContentManager : public QThread
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> buttons READ buttons NOTIFY buttonsChanged)
    Q_PROPERTY(QList<QObject*> mainWindows READ mainWindows NOTIFY mainWindowsChanged)
public:
    void run();
    ContentManager();
    static ContentManager* Instance();
    void setQmlEngine( QQmlApplicationEngine* qmlEngine);
    QList<QObject*> buttons();
    QList<QObject*> mainWindows();
    Q_INVOKABLE void visibleChanged(bool visible);

private slots:
    void focusRequest(int contentID);
    void stringTransmitRequest(int id, QStringList display);
public slots:
    void load();

signals:
    void buttonsChanged();
    void mainWindowsChanged();
private:
    QQmlApplicationEngine* qmlEngine;
    QQuickItem* contentPanel;

    QList<ContentBasic*> contentList;
    QList<QObject*> buttonList;
    QList<QObject*> mainWindowList;
    int currentFocus;
};



#endif // CONTENTMANAGER_H
