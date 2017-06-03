#ifndef CONTENTFINGER_H
#define CONTENTFINGER_H

#include "contentbasic.h"

class ContentFinger : public ContentBasic
{
    Q_OBJECT
public:
    ContentFinger(int id, QQmlApplicationEngine* qmlEngine);

    QString name();

private slots:
    void send();
};

#endif // CONTENTFINGER_H
