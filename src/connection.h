#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QStringList>
#include "serialport.h"

class connection : public QObject
{
    typedef enum {
        id_assign = 0x00,
        data_transmit = 0x01
    } commandwords;

    typedef enum {
        character_update = 0x01,
        brightness_update = 0x02
    } datatypes;

    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(int displayCount READ displayCount NOTIFY displayCountChanged)
public:
    explicit connection(QObject *parent = 0);
    void setConnected(bool c);
    bool connected();
    QString message();
    void initID();
    void sendDisplayText(int id, char* text);
    int displayCount();
    void writeText(char text[][21]);
    void writeText(QStringList strings);
signals:
    void connectedChanged();
    void messageChanged();
    void displayCountChanged();

public slots:
    void serialConnect();
    void connectionSuccess();
    void connectionError(QString msg);
    void send();
    void sendText();
    void processSerial(uint8_t* buffer, size_t length);


private:
    uint8_t calc_checksum(uint8_t* data, uint8_t length);
    void sendDatatransfer(int id, datatypes mode, uint8_t* buffer, size_t length);

    SerialPort* serial;
    QString msg;

    int numberOfDisplays;
};

#endif // CONNECTION_H
