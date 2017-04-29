#include "connection.h"
#include <QDebug>
#include <termios.h>
#include "messagecontroller.h"
connection::connection(QObject *parent) : QObject(parent)
{
    serial=NULL;
    numberOfDisplays=-1;
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
    if(serial)
        return true;
    else
        return false;
}

QString connection::message()
{
    return msg;
}

void connection::send()
{
    initID();

}

void connection::sendText()
{
    char txt[4][21];

    //strcpy(txt[0],"Hallo welt geht das?");
   // strcpy(txt[1],"ABCDEFGHIJKLMNOPQRST");
    //strcpy(txt[2],"UVWXYZ0123456789ABCD");
   // strcpy(txt[3],"EFGHIJKLMNOPQRSTUVWX");

  //  writeText(txt);

    writeText(QStringList() << "Das ist so cool" << "ROFL");
}

void connection::writeText(char text[][21])
{
    char buffer[21];
    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=text[y][x];
    sendDisplayText(1,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=text[y+2][x];
    sendDisplayText(0,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=text[y][x+10];
    sendDisplayText(3,buffer);

    for(int y=0; y<2; y++)
        for(int x=0; x<10;x++)
            buffer[10*y+x]=text[y+2][x+10];
    sendDisplayText(2,buffer);


}

void connection::writeText(QStringList strings)
{
    char txt[4][21]={0};

    for(int i=0; i < 4 && i < strings.length(); i++)
    {
        const char* tmp = strings[i].toStdString().c_str();
        strncpy(txt[i],tmp,20);
    }
    writeText(txt);
}

void connection::processSerial(uint8_t *buffer, size_t length)
{
    qDebug() << "Got " << length << " bytes";
    qDebug() << "Received: ";
    for(unsigned int i=0; i < length; i++)
        qDebug("0x%02X", (unsigned int)buffer[i]);

    if(length>1)
    {
        switch(buffer[0])
        {
            case id_assign: numberOfDisplays=buffer[1];
                            emit displayCountChanged();
                            break;
        }


    }

    delete buffer;
}

void connection::serialConnect()
{
    if(!serial)
    {
        serial = new SerialPort();

        qDebug() << connect(serial,SIGNAL(connected()),this,SLOT(connectionSuccess()));
        connect(serial,SIGNAL(errorSignal(QString)),this,SLOT(connectionError(QString)));
        connect(serial,SIGNAL(newData(uint8_t*,size_t)),this,SLOT(processSerial(uint8_t*,size_t)));
        serial->connect("/dev/ttyUSB0",B9600);
        qDebug() << "Connection created";
        serial->start();
        emit connectedChanged();
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
    sendDatatransfer(id,character_update,(uint8_t*)text,20);
}

int connection::displayCount()
{
    return numberOfDisplays;
}

void connection::connectionSuccess()
{
    msg="Connected";
    emit messageChanged();
}

void connection::connectionError(QString msg)
{
    qDebug() << "Connection error: " << msg;

    MessageController::Instance()->addMessage(msg);

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

    serial->writeBytes(data,length+5);
}
