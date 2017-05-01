#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QStringList>
#include <QByteArray>
#include <QList>
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

    typedef struct {
        int id;
        uint8_t* data;
        size_t length;
        datatypes mode;
    } message_t;

    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int displayCount READ displayCount NOTIFY displayCountChanged)
    Q_PROPERTY(QByteArray framebufferContent READ framebufferContent NOTIFY framebufferContentChanged)

public:
    explicit connection(QObject *parent = 0);
    void setConnected(bool c);
    bool connected();
    void initID();
    void sendDisplayText(int id, char* text);
    int displayCount();
    void syncFramebuffer();
    void writeText(QStringList strings);
    Q_INVOKABLE void writeText(QString line1,QString line2,QString line3,QString line4);
    Q_INVOKABLE void writeText(QString text);
    Q_INVOKABLE void setBrightness(double value);
    QByteArray framebufferContent();
signals:
    void connectedChanged();
    void displayCountChanged();
    void framebufferContentChanged();

public slots:
    void serialConnect();
    void connectionSuccess();
    void connectionError(QString msg);
    void sendText();
    void processSerial(uint8_t* buffer, size_t length);


private:
    uint8_t calc_checksum(uint8_t* data, uint8_t length);
    void sendDatatransfer(int id, datatypes mode, uint8_t* buffer, size_t length);
    void processStatemachine(uint8_t data);

    SerialPort* serial;

    QList<message_t*> packageList;
    int numberOfDisplays;
    char framebuffer[4][21] ;

};

#endif // CONNECTION_H
