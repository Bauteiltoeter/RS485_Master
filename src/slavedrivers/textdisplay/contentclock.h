#ifndef CONTENTCLOCK_H
#define CONTENTCLOCK_H

#include "contentbasic.h"
#include <QString>

class ContentClock : public ContentBasic
{
public:
    ContentClock(int id, QQmlApplicationEngine* qmlEngine);

    QString name();
    void run();
    QString headerText();


private:
    QString oldDate;
    QString oldTime;
};

#endif // CONTENTCLOCK_H
