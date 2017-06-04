#include "busmaster.h"
#include "messagecontroller.h"
#include <termios.h>
#include <QDebug>

Busmaster::Busmaster()
{

    qDebug() << "Creating a busmaster";
    serial=NULL;
    processing=NULL;

    sm = SlaveManager::Instance();

}

Busmaster* Busmaster::Instance()
{
    static Busmaster* singleton = new Busmaster();
    return singleton;
}

void Busmaster::connect()
{
    qDebug() << "Connecting busmaster";

    serial = new SerialPort();

    QObject::connect(serial,SIGNAL(connected()),this,SLOT(serialConnected()));
    QObject::connect(serial,SIGNAL(errorSignal(QString)),this,SLOT(serialError(QString)));
    QObject::connect(serial,SIGNAL(newData(uint8_t*,size_t)),SLOT(newSerialData(uint8_t*,size_t)));
    serial->connect("/dev/ttyUSB0",B115200);

    if(serial)
    {
        serial->start();
        setReceive();
        start();
    }
}

void Busmaster::detectSlaves()
{
    qDebug() << "Searching for slaves";

    Busaction::Busaction_t* tmp = new Busaction::Busaction_t;
    tmp->type=Busaction::ID_INIT;
    actions.append(tmp);

}

void Busmaster::serialError(QString msg)
{
    MessageController::Instance()->addMessage(new Message(true,msg));
}

void Busmaster::serialConnected()
{
    MessageController::Instance()->addMessage(new Message(false,"Connected"));
}

void Busmaster::newSerialData(uint8_t *data, size_t length)
{
    for(size_t i=0; i < length; i++)
    {
        qDebug() << "Add byte to queue: " << data[i];
        incomingBytes.append(data[i]);
    }
}

uint16_t Busmaster::getFreeId()
{
    return 0xABCD;
}

uint16_t Busmaster::calc_checksum(uint8_t *data, uint16_t length)
{
    uint16_t sum=0;

    for(uint16_t i=0; i < length; i++)
    {
        sum^= data[i];
    }

    return sum;
}

void Busmaster::setTransmit()
{
    qDebug() << "Setting DTR high";

    if(serial)
        serial->setDTR(true);
}

void Busmaster::setReceive()
{
    qDebug() << "Setting DTR low";
    if(serial)
        serial->setDTR(false);
}



void Busmaster::run()
{
    while(1)
    {
        if(processing && processing->myTimer.elapsed() > 500)
        {
            qDebug() << "Timeout!";

            switch(processing->type)
            {

                case Busaction::ID_INIT: MessageController::Instance()->addMessage(new Message(false, "No new slaves")); break;
            }

          //  delete processing;
            processing=NULL;

        }

        if(!incomingBytes.empty())
        {
            if(processing==NULL)
            {
                MessageController::Instance()->addMessage(new Message(true, "Stray bytes on bus!"));
                qDebug() << "Stray bytes on the bus!";
                incomingBytes.clear();
            }
            else
            {
                switch( processing->type)
                {
                    case Busaction::ID_INIT:
                        if(incomingBytes.size()>=6)
                        {
                            qDebug() << "Processing response";

                            uint8_t buffer[6];
                            for(int i=0; i < 6; i++)
                            {
                                buffer[i] = incomingBytes.first();
                                incomingBytes.removeFirst();
                            }

                            uint16_t id = buffer[0]<<8 |buffer[1];
                            uint16_t hw_id = buffer[2]<<8 | buffer[3];
                            uint16_t checksum = buffer[4]<<8 | buffer[5];

                            sm->createSlave(id,hw_id);

                            MessageController::Instance()->addMessage(new Message(false,"Detected new slave\n ID: " + QString::number(id) + "\nHardware ID: " + QString::number(hw_id)));
                            delete processing;
                            processing=NULL;

                        }

                    break;
                }
            }

        }


        if(!actions.empty() && processing==NULL)
        {
            qDebug() << "Oh stuff to do!";

            processing = actions.first();
            actions.pop_front();
            processing->myTimer.start();
            switch(processing->type)
            {
                case Busaction::ID_INIT:
                    uint8_t buffer[5];
                    buffer[0] = 0xAA;
                    buffer[1] = 0xFF;
                    buffer[2] = 0xFF;

                    uint16_t newId = getFreeId();
                    buffer[3] = newId>>8;
                    buffer[4] = newId;
                    setTransmit();
                    serial->writeBytes(buffer,5);
                    setReceive();
                break;
            }


        }
        //serial->setDTR(false);
        msleep(10);
       // serial->setDTR(true);

      //  qDebug() << "Busmaster running";
   //     msleep(1000);
    }
}
