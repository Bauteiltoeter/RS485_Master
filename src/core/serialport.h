#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QThread>
#include <termios.h>

class SerialPort : public QThread
{
    Q_OBJECT
public:
    SerialPort();
    ~SerialPort();
    int connect(QString name, speed_t speed);
    void run();
    void stop();
    void writeBytes(uint8_t* bytes, size_t length);
    bool isConnected();
    void setDTR(bool state);

signals:
    void errorSignal(QString msg);
    void connected();
    void newData(uint8_t* buffer, size_t length);

private:
    int USB;
    bool stopNow;
};

#endif // SERIALPORT_H
