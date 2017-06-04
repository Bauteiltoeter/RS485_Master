#ifndef SLAVEMANAGER_H
#define SLAVEMANAGER_H

#include <QObject>
#include <QVector>
#include "basicslave.h"

class SlaveManager : public QObject
{
    Q_OBJECT


public:
    SlaveManager();


private:
    QVector<BasicSlave*> knownSlaves();
};

#endif // SLAVEMANAGER_H
