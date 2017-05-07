#include "contentclock.h"
#include <QDebug>
#include <QDateTime>

ContentClock::ContentClock(int id, QQmlApplicationEngine* qmlEngine)
    : ContentBasic(id,qmlEngine)
{
    createGUI("qrc:/qml/ContentClock.qml");
}

QString ContentClock::name()
{
    return "Clock";
}

void ContentClock::run()
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
