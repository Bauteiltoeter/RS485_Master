#include "connection.h"
#include <QDebug>
#include <termios.h>
#include "messagecontroller.h"
connection::connection(QObject *parent) : QObject(parent)
{
    serial=NULL;
    numberOfDisplays=-1;
    memset(framebuffer,0,sizeof(framebuffer));
}

void connection::setConnected(bool c)
{
    if(c==false)
    {
        if(serial)
        {
            serial->stop();
            delete serial;
        }
        serial=NULL;
        emit connectedChanged();
    }
    else
    {
        serialConnect();

    }
}

bool connection::connected()
{
    if(serial && serial->isConnected())
        return true;
    else
        return false;
}



void connection::sendText()
{

    writeText(QStringList() <<  "Viele gruesse in die" <<
                                "Runde aus Ingolstadt" <<
                                "wuenscht Torben");
}

void connection::syncFramebuffer()
{
    char buffer[21];

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=framebuffer[y][x];
    sendDisplayText(1,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
           buffer[10*y+x]=framebuffer[y+2][x];
    sendDisplayText(0,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=framebuffer[y][x+10];
    sendDisplayText(3,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=framebuffer[y+2][x+10];
    sendDisplayText(2,buffer);

    emit framebufferContentChanged();
}

void connection::writeText(QStringList strings)
{


    for(int i=0; i < 4 && i < strings.length(); i++)
    {
        qDebug() << "strncpy index: " << i;
        QString tmp =  strings[i];
        QByteArray array = tmp.toLocal8Bit();
        char* buffer = array.data();

        strncpy(framebuffer[i],buffer,21);
    }


    syncFramebuffer();
}

void connection::writeText(QString line1, QString line2, QString line3, QString line4)
{
    writeText(QStringList() << line1 << line2 << line3 << line4);
}

void connection::writeText(QString text)
{
    QStringList tmp = text.split('\n');
    writeText(tmp);
}

void connection::setBrightness(double value)
{
    uint8_t buffer = (uint8_t) value;

    qDebug() << "setBrigtness: " << buffer;
    qDebug() << "NumberOfDisplays:" << numberOfDisplays;

    for(int i=0; i<4;i++)
        sendDatatransfer(i,brightness_update,&buffer,1);
}

QByteArray connection::framebufferContent()
{

    QByteArray tmp;

    for(int i=0; i < 84; i++)
    {
        if(i==20) i++;
        if(i==41) i++;
        if(i==62) i++;
        tmp.append(framebuffer[0][i]);

    }
    qDebug()  << "fetching framebuffer content:" << tmp;

    return tmp;

}


void connection::processSerial(uint8_t *buffer, size_t length)
{
    qDebug() << "Got " << length << " bytes";
    qDebug() << "Received: ";
    for(unsigned int i=0; i < length; i++)
        qDebug("0x%02X", (unsigned int)buffer[i]);

    for(size_t i=0; i<length; i++)
        processStatemachine(buffer[i]);

    delete buffer;
}

void connection::processStatemachine(uint8_t data)
{


    //numberOfDisplays=buffer[1];
   //  emit displayCountChanged();
}



void connection::serialConnect()
{
    if(serial && !serial->isConnected())
    {
       // serial->deleteLater();
        serial=NULL;
    }

    if(!serial )
    {
        serial = new SerialPort();

        qDebug() << connect(serial,SIGNAL(connected()),this,SLOT(connectionSuccess()));
        connect(serial,SIGNAL(errorSignal(QString)),this,SLOT(connectionError(QString)));
        connect(serial,SIGNAL(newData(uint8_t*,size_t)),this,SLOT(processSerial(uint8_t*,size_t)));
        serial->connect("/dev/ttyUSB0",B9600);
        qDebug() << "Connection created";
        serial->start();
        emit connectedChanged();
        initID();
    }
    else
    {
        qDebug() << "Connection already created";
    }
}

void connection::initID()
{
    uint8_t data[] = {0,0};
    serial->writeBytes(data,2);
}

void connection::sendDisplayText(int id, char* text)
{
    qDebug("connection::sendDisplayText(%d, %s)",id,text);

    sendDatatransfer(id,character_update,(uint8_t*)text,20);
}

int connection::displayCount()
{
    return numberOfDisplays;
}

void connection::connectionSuccess()
{

   MessageController::Instance()->addMessage(new Message(false,"Connected"));

}

void connection::connectionError(QString msg)
{
    qDebug() << "Connection error: " << msg;

    MessageController::Instance()->addMessage(new Message(true,msg));

}

uint8_t connection::calc_checksum(uint8_t* data, uint8_t length)
{
    uint8_t temp=0;
    for(uint16_t i=0; i < length; i++)
    {
        temp^=data[i];
    }
    return temp;
}

void connection::sendDatatransfer(int id, connection::datatypes mode, uint8_t *buffer, size_t length)
{
    uint8_t data[256];
    data[0] = data_transmit;
    data[1] = id; //message id
    data[2] = length+2; //length+modeword+checksum
    data[3] = mode;
    memcpy(data+4,buffer,length);
    data[length+4]= calc_checksum(data+3,length+1); //checksum

    char debug[256];
    memcpy(debug,data,256);

    if(serial)
        serial->writeBytes(data,length+5);
}

