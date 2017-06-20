#ifndef CONTENTBASIC_H
#define CONTENTBASIC_H

#include <QObject>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QStringList>

class ContentBasic : public QObject
{
    Q_OBJECT
public:
    ContentBasic(int id, QQmlApplicationEngine* qmlEngine);

    virtual QString name();
    virtual void run();
    virtual QString headerText();
    virtual QString footerText();
    QObject* mainWindow();
    int getContentID();
signals:
    void requestFocus(int id);
    void requestStringTransmit(int contentID,QStringList display);

public slots:
    void activate();

protected:
    void createGUI(QString resource);
    QObject* gui;
    int contentID;

private:



    QQmlApplicationEngine* qmlEngine;

};

#endif // CONTENTBASIC_H
