#ifndef SLAVEMANAGER_H
#define SLAVEMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QXmlStreamReader>
#include "basicslave.h"

class SlaveManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString slaveNames READ slaveNames NOTIFY slaveNamesChanged)
public:
    SlaveManager();
    static SlaveManager* Instance();

    void createSlave(uint16_t id, uint16_t hw_id);
    QString slaveNames();

signals:
    void slaveNamesChanged();

private:
    void loadSlaves(QString file);
    void processSlaves();
    void processSlave();
    QString readNextText();
    QVector<BasicSlave*> knownSlaves;
    QXmlStreamReader xml;
};

#endif // SLAVEMANAGER_H
