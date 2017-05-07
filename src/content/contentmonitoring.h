#ifndef CONTENTMONITORING_H
#define CONTENTMONITORING_H

#include "contentbasic.h"

class ContentMonitoring : public ContentBasic
{
    Q_OBJECT

public:
    ContentMonitoring(int id, QQmlApplicationEngine* qmlEngine);

    QString name();
    void run();
};

#endif // CONTENTMONITORING_H
