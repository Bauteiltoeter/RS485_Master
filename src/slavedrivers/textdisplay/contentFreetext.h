#ifndef CONTENTFREETEXT_H
#define CONTENTFREETEXT_H

#include "contentbasic.h"
#include <QString>

class ContentFreetext : public ContentBasic
{
public:
    ContentFreetext(int id, QQmlApplicationEngine* qmlEngine);

    QString name();
    void run();
    QString headerText();


private:
    QString oldDate;
    QString oldTime;
};

#endif // CONTENTFREETEXT_H
