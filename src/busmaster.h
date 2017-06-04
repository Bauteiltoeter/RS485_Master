#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QThread>
#include "serialport.h"
#include <QList>
#include <QTime>
#include <time.h>
#include <stdint.h>
#include "slavemanager.h"

#define TIMEOUT_MS 2

namespace Busaction {
    typedef enum {
        ID_INIT,
        TRANSMIT_MASTER_SLAVE,
        TRANSMIT_SLAVE_MASTER
    } Action_type;

    typedef void (*bus_callback_t)(void);

    typedef struct {
        uint16_t id;
        uint16_t msg_id;
        uint8_t length;
        uint8_t* data;
        uint16_t checksum; //zum vergleichen
    } Transfer_data_t;

    typedef struct {
        Action_type type;
        QTime myTimer;
        Transfer_data_t* transfer_data;
        bus_callback_t error;
        bus_callback_t success;
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
    Q_INVOKABLE void pingSlave();

private slots:
    void serialError(QString msg);
    void serialConnected();
    void newSerialData(uint8_t* data, size_t length);

private:
    uint16_t getFreeId();
    uint16_t calc_checksum(uint8_t* data, uint16_t length);
    void transmit_master_slave(uint16_t id, uint16_t msg_id, uint8_t length, uint8_t* data);
    void transmit_master_slave(uint16_t id, uint16_t msg_id, uint8_t length, uint8_t* data, Busaction::bus_callback_t success, Busaction::bus_callback_t error);
    void clearProcessing();
    void setTransmit();
    void setReceive();

    SerialPort* serial;

    QList<Busaction::Busaction_t*> actions;
    Busaction::Busaction_t* processing;
    QList<uint8_t> incomingBytes;
    SlaveManager* sm;


};

#endif // COMMUNICATOR_H
