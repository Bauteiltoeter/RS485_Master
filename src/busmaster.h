#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QThread>
#include "serialport.h"
#include <QList>
#include <QTime>
#include <time.h>
#include <stdint.h>

#define TIMEOUT_MS 2

namespace Busaction {
    typedef enum {
        ID_INIT
    } Action_type;

    typedef struct {
        Action_type type;
    } Busaction_t;
}

class Busmaster : public QThread
{
    Q_OBJECT

public:
    Busmaster();
    void run();
    static Busmaster* Instance();
    Q_INVOKABLE void connect();
    Q_INVOKABLE void detectSlaves();

private slots:
    void serialError(QString msg);
    void serialConnected();
    void newSerialData(uint8_t* data, size_t length);

private:
    uint16_t getFreeId();
    uint16_t calc_checksum(uint8_t* data, uint16_t length);
    void setTransmit();
    void setReceive();

    SerialPort* serial;

    QList<Busaction::Busaction_t*> actions;
    Busaction::Busaction_t* processing;
    QList<uint8_t> incomingBytes;


};

#endif // COMMUNICATOR_H
