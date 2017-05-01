#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QObject>
#include <QThread>
#include "serialport.h"
#include <QList>
#include <QTime>
#include <time.h>

#define TIMEOUT_MS 2

class Communicator : public QThread
{
    Q_OBJECT
public:


    typedef enum {
        id_assign = 0x00,
        data_transmit = 0x01
    } commandwords;

    typedef enum {
        character_update = 0x01,
        brightness_update = 0x02
    } datatypes;

    typedef struct {
        int id;
        uint8_t* data;
        size_t length;
        datatypes mode;
        clock_t sendTime;
        int retrycounter;
    } package_t;

    Communicator();
    ~Communicator();
    void run();

    void serialConnect();
    void serialDisconnect();
    bool isConnected();

    package_t* getNewPackage();
    void sendPackage(package_t* package);

private slots:
    void connectionSuccess();
    void connectionError(QString msg);
    void processData(uint8_t* buffer, size_t length);

signals:
    void serialSuccess();
    void serialError(QString msg);
    void connectionStatusChanged();

private:
    void initID();
    uint8_t calc_checksum(uint8_t* data, uint8_t length);
    void sendDatatransfer(int id, datatypes mode, uint8_t* buffer, size_t length);
    void tickStatemachine(uint8_t byte);
    package_t* fetch_new_byId(int id);


    SerialPort* serial;
    QVector<package_t*> newPackages;
    package_t* sendPackages[4];

};

#endif // COMMUNICATOR_H
