#ifndef SLAVEMANAGER_H
#define SLAVEMANAGER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QMap>
#include <QXmlStreamReader>
#include <QQmlApplicationEngine>
#include "basicslave.h"

class SlaveManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString slaveNames READ slaveNames NOTIFY slaveNamesChanged)
public:
    SlaveManager();
    static SlaveManager* Instance();

    void createSlave(uint16_t id, uint16_t hw_id);
    void connected();
    QString slaveNames();
    void setQmlEngine(QQmlApplicationEngine* engine);
    uint16_t getNextFreeId();
    Q_INVOKABLE void loadGUI();
    Q_INVOKABLE void pingSlave();
    Q_INVOKABLE void resetSlaveID();
    Q_INVOKABLE void removeSlave();
    Q_INVOKABLE void testSlave();

private slots:
    void transmitSuccess(int t_id);
    void transmitError(int t_id);

signals:
    void slaveNamesChanged();

private:
    void loadSlaves(QString filename);
    void saveSlaves(QString filename);
    void processSlaves();
    void processSlave();
    BasicSlave *getSelected();
    QString readNextText();
    QVector<BasicSlave*> knownSlaves;
    QXmlStreamReader xml;

    QString slave_filename;
    QMap<int, BasicSlave*> pingMap;
    QQmlApplicationEngine* qmlEngine;

    uint16_t nextFreeId;
};

#endif // SLAVEMANAGER_H
