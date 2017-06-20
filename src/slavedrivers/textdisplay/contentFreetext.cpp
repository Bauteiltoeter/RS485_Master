#include "contentFreetext.h"
#include <QDebug>
#include <QDateTime>

ContentFreetext::ContentFreetext(int id, QQmlApplicationEngine* qmlEngine)
    : ContentBasic(id,qmlEngine)
{
    createGUI("qrc:/qml/ContentFreetext.qml");
}

QString ContentFreetext::name()
{
    return "Free text";
}

void ContentFreetext::run()
{
    QStringList tmp;

    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();

    time[2] = '.';
    time[5] = '.';
    tmp.append(date);
    tmp.append(time);

    if(date!=oldDate || time!=oldTime)
        emit requestStringTransmit(contentID,tmp);

    oldTime = time;
    oldDate = date;
}

QString ContentFreetext::headerText()
{
    return "Freetext writer";
}
