#ifndef CONTENTMONITORING_H
#define CONTENTMONITORING_H

#include "contentbasic.h"
#include "qicmp.h"
#include "monitoredhost.h"
#include <QList>


class ContentMonitoring : public ContentBasic
{
    Q_OBJECT

public:
    ContentMonitoring(int id, QQmlApplicationEngine* qmlEngine);

    QString name();
    void run();

private slots:


private:
    QList<MonitoredHost*> hostList;

    QStringList hosts;
};

#endif // CONTENTMONITORING_H
