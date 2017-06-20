#include "busmaster.h"
#include "messagecontroller.h"
#include <termios.h>
#include <QDebug>
#include <stdio.h>

Busmaster::Busmaster()
{

    qDebug() << "Creating a busmaster";
    serial=NULL;
    processing=NULL;

    sm = SlaveManager::Instance();
    transmit_id=0;
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
        sm->connected();


    }
}

int Busmaster::detectSlaves()
{
    qDebug() << "Searching for slaves";

    Busaction::Busaction_t* tmp = new Busaction::Busaction_t;
    tmp->type=Busaction::ID_INIT;
    tmp->transfer_data=NULL;
    tmp->t_id=transmit_id++;
    actions.append(tmp);
    return tmp->t_id;
}

int Busmaster::pingSlave(uint16_t slave_id)
{
    return transmit_master_slave(slave_id,1,0,NULL);
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
    return sm->getNextFreeId();
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

int Busmaster::transmit_master_slave(uint16_t id, uint16_t msg_id, uint8_t length, uint8_t *data)
{
    qDebug() << "Transmit from master to slave: id: " << id << " msg_id: " << msg_id << " length: " << length;

    for(int i=0; i < length; i++)
        printf("Data: %02X\n",data[i]);

    Busaction::Busaction_t* tmp = new Busaction::Busaction_t;
    tmp->type=Busaction::TRANSMIT_MASTER_SLAVE;
    tmp->t_id=transmit_id++;

    tmp->transfer_data= new Busaction::Transfer_data_t;

    tmp->transfer_data->data= data;
    tmp->transfer_data->id = id;
    tmp->transfer_data->length = length;
    tmp->transfer_data->msg_id = msg_id;
    actions.append(tmp);

    return tmp->t_id;
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

void Busmaster::clearProcessing()
{
    if(processing)
    {
        if(processing->transfer_data)
            delete processing->transfer_data;
        delete processing;
    }

    processing=NULL;
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
                case Busaction::TRANSMIT_MASTER_SLAVE: /*MessageController::Instance()->addMessage((new Message(true,"Slave does not responde"))); */break;
            }

            emit transmitError(processing->t_id);


            clearProcessing();

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
                            emit transmitSuccess(processing->t_id);
                            clearProcessing();
                        }

                    break;

                    case Busaction::TRANSMIT_MASTER_SLAVE:
                        if(incomingBytes.size()>=3)
                        {
                            uint8_t buffer[3];
                            for(int i=0; i < 3; i++)
                            {
                                buffer[i] = incomingBytes.first();
                                incomingBytes.removeFirst();
                            }

                            uint16_t checksum = buffer[1]<<8|buffer[2];

                            if (buffer[0] != 0xAA || checksum!=processing->transfer_data->checksum)
                            {
                                MessageController::Instance()->addMessage(new Message(true,"Checksum error"));
                                emit transmitError(processing->t_id);
                            }
                            else
                            {
                                emit transmitSuccess(processing->t_id);
                            }
                            clearProcessing();

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
                {
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
                }
                break;

                case Busaction::TRANSMIT_MASTER_SLAVE:
                {
                    qDebug() << "Sending master->slave bytes";
                    uint8_t buffer[12 + processing->transfer_data->length];
                    buffer[0] = 0xAA;
                    buffer[1] = processing->transfer_data->id>>8;
                    buffer[2] = processing->transfer_data->id;
                    buffer[3] = processing->transfer_data->msg_id>>8;
                    buffer[4] = processing->transfer_data->msg_id;
                    buffer[5] = 0x01; //master->slave transmit
                    buffer[6] = processing->transfer_data->length;
                    if(processing->transfer_data->length>0)
                        memcpy(&buffer[7],processing->transfer_data->data,processing->transfer_data->length);
                    processing->transfer_data->checksum= calc_checksum(buffer,6+processing->transfer_data->length);
                    buffer[7+processing->transfer_data->length] = processing->transfer_data->checksum>>8;
                    buffer[8+processing->transfer_data->length] = processing->transfer_data->checksum;

                    setTransmit();
                    serial->writeBytes(buffer,9+processing->transfer_data->length);
                    setReceive();
                }
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
