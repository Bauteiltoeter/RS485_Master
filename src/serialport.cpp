#include "serialport.h"
#include <QDebug>
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definition

SerialPort::SerialPort()
{
    stopNow=false;
}

SerialPort::~SerialPort()
{
    qDebug() << "Deleting serial port";
}

void SerialPort::connect(QString name, speed_t speed)
{
    SerialPort();
    qDebug() << "Opening SerialPort: " << name;

    /* Open File Descriptor */
    USB = open( name.toStdString().c_str() , O_RDWR  );

    /* Error Handling */
    if ( USB < 0 )
    {
        emit errorSignal("USB handler invalid");
        return;
    }

    /* *** Configure Port *** */
    struct termios tty;
    memset (&tty, 0, sizeof tty);

    /* Error Handling */
    if ( tcgetattr ( USB, &tty ) != 0 )
    {
        qDebug() << "Error: tcgerattr";
        emit errorSignal("tcgerattr");
        return;
    }

    /* Set Baud Rate */
    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    /* Setting other Port Stuff */
    tty.c_cflag     &=  ~PARENB;        // Make 8n1
    tty.c_cflag     &=  ~CSTOPB;
    tty.c_cflag     &=  ~CSIZE;
    tty.c_cflag     |=  CS8;
    tty.c_cflag     &=  ~CRTSCTS;       // no flow control
    tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
    tty.c_oflag     =   0;                  // no remapping, no delays
    tty.c_cc[VMIN]      =   0;                  // read doesn't block
    tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout

    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
    tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    tty.c_oflag     &=  ~OPOST;              // make raw

    /* Flush Port, then applies attributes */
    tcflush( USB, TCIFLUSH );

    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
    {
        qDebug() << QString("Error") + errno  + " from tcsetattr";
        errorSignal(QString("Error") + errno  + " from tcsetattr");
        return;
    }

    qDebug() << "emit connected";
    emit connected();

}

void SerialPort::run()
{
    while(!stopNow)
    {
        uint8_t buf [256];
        memset (&buf, '\0', sizeof buf);
        int n = read( USB, &buf , sizeof buf );

        if(n>0)
        {
            uint8_t* store = new uint8_t[n];
            memcpy(store,buf,n);
            emit newData(store,n);

        }

    }
}

void SerialPort::stop()
{
    stopNow=true;
}

void SerialPort::writeBytes(uint8_t* bytes, size_t length)
{
    qDebug() << "Sending bytes:";
    for(unsigned int i=0; i < length; i++)
        qDebug("0x%02X      %d", (unsigned int)bytes[i],(unsigned int)bytes[i]);
    write( USB, bytes, length );
}
