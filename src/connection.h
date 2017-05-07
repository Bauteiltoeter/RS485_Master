#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QStringList>
#include <QByteArray>
#include <QList>
#include "serialport.h"
#include "communicator.h"

class connection : public QObject
{


    Q_OBJECT
    Q_PROPERTY(bool connected READ connected WRITE setConnected NOTIFY connectedChanged)
    Q_PROPERTY(int displayCount READ displayCount NOTIFY displayCountChanged)
    Q_PROPERTY(QByteArray framebufferContent READ framebufferContent NOTIFY framebufferContentChanged)

public:
    explicit connection(QObject *parent = 0);
    ~connection();
    static connection* Instance();

    void setConnected(bool c);
    bool connected();


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
   // void serialConnect();
    void connectionSuccess();
    void connectionError(QString msg);
    void connectionStatusChanged();



private:

    void processStatemachine(uint8_t data);

    Communicator communicator;



    int numberOfDisplays;
    char framebuffer[4][21] ;

};

#endif // CONNECTION_H
