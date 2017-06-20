#ifndef CONTENTPOWERMETER_H
#define CONTENTPOWERMETER_H

#include "contentbasic.h"
#include <QString>

class ContentPowermeter : public ContentBasic
{
public:
    ContentPowermeter(int id, QQmlApplicationEngine* qmlEngine);

    QString name();
    void run();
    QString headerText();
    QString footerText();

private:
    QString oldDate;
    QString oldTime;
};

#endif // CONTENTPOWERMETER_H
