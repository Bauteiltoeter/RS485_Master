#include "communicator.h"
#include "messagecontroller.h"
#include <QDebug>

Communicator::Communicator()
{
    serial=NULL;
    sendPackages[0]=NULL;
    sendPackages[1]=NULL;
    sendPackages[2]=NULL;
    sendPackages[3]=NULL;
}

Communicator::~Communicator()
{

}

void Communicator::run()
{
    while(1)
    {
        msleep(10);

        if(!newPackages.empty())
        {
            for(int i=0; i<4; i++)
            {
                if(sendPackages[i]==NULL)
                {
                    package_t* p = fetch_new_byId(i);
                    if(p)
                    {
                        sendPackages[i] = p;
                        sendPackages[i]->sendTime = clock()/ CLOCKS_PER_SEC;
                        sendDatatransfer(p->id,p->mode,p->data,p->length);

                    }
                }
            }
        }

        for(int i=0; i<4; i++)
        {
            if(sendPackages[i] &&( (sendPackages[i]->sendTime+TIMEOUT_MS) < clock()/ CLOCKS_PER_SEC))
            {
                if(sendPackages[i]->retrycounter<3)
                {
                    qDebug() << "Timeout " << i << "!";
                    package_t* p = sendPackages[i];
                    sendPackages[i]->sendTime = clock()/CLOCKS_PER_SEC;
                    sendDatatransfer(p->id,p->mode,p->data,p->length);
                    sendPackages[i]->retrycounter++;
                }
                else
                {
                    MessageController::Instance()->addMessage(new Message(true,"Slave not responding"));
                }

            }

        }
    }
}

Communicator::package_t* Communicator::fetch_new_byId(int id)
{
    for(int i=0; i < newPackages.size(); i++)
    {
        if(newPackages[i]->id==id)
        {
            package_t* tmp = newPackages[i];
            newPackages.remove(i);
            return tmp;
        }
    }

    return NULL;
}

void Communicator::serialConnect()
{
    if(serial && !serial->isConnected())
    {
        serial=NULL;
    }

    if(!serial )
    {
        qDebug() << "Creating new serial";
        serial = new SerialPort();

        connect(serial,SIGNAL(connected()),this,SLOT(connectionSuccess()));
        connect(serial,SIGNAL(errorSignal(QString)),this,SLOT(connectionError(QString)));
        connect(serial,SIGNAL(newData(uint8_t*,size_t)),this,SLOT(processData(uint8_t*,size_t)));
        serial->connect("/dev/ttyUSB0",B9600);

        qDebug() << "Connection created";
        serial->start();
        emit connectionStatusChanged();
        //emit connectedChanged();
        initID();
    }
    else
    {
        qDebug() << "Connection already created";
    }
}

void Communicator::serialDisconnect()
{

}

bool Communicator::isConnected()
{
    if(serial && serial->isConnected())
    {
        return true;
    }

    return false;
}

Communicator::package_t *Communicator::getNewPackage()
{
    package_t* tmp = new package_t;
    tmp->retrycounter=0;
    return tmp;
}

void Communicator::sendPackage(Communicator::package_t *package)
{
    newPackages.append(package);
}

void Communicator::connectionSuccess()
{
    qDebug() << "ConnectionSuccess";
    emit serialSuccess();
}

void Communicator::connectionError(QString msg)
{
    qDebug() << "ConnectionError" << msg;
    emit serialError(msg);
}

void Communicator::processData(uint8_t* buffer, size_t length)
{
    for(int i=0; i<length;i++)
    {
        tickStatemachine(buffer[i]);


    }
}

void Communicator::tickStatemachine(uint8_t byte)
{
    static int state = 0; // 0: waiting
    static uint8_t mode;
    static int datacounter=0;
    static uint8_t data[4];

    switch(state)
    {
    case 0:
        mode=byte;
        datacounter=0;
        state=1;
        break;
    case 1:
        if(mode==0)
        {
            qDebug() << "Detecting answer to init, " << byte << " displays found";
            state=0;
        }
        else if(mode==1)
        {
            data[datacounter]=byte;
            datacounter++;
            if(datacounter>=3)
            {
                state=0;
                if(data[2] == 0)
                {
                    qDebug() << "received ack for id" << data[0];
                    delete sendPackages[data[0]];
                    sendPackages[data[0]] = NULL;
                }
                else
                {
                    qDebug() << "Received Nack for id" << data[0];

                }

                //qDebug() << "Receiving answer: " << (int)data[0]<< (int)data[1]<< (int)data[2]<< (int)data[3];
            }
        }
        break;
    }
}



uint8_t Communicator::calc_checksum(uint8_t* data, uint8_t length)
{
    uint8_t temp=0;
    for(uint16_t i=0; i < length; i++)
    {
        temp^=data[i];
    }
    return temp;
}

void Communicator::sendDatatransfer(int id, Communicator::datatypes mode, uint8_t *buffer, size_t length)
{
    qDebug() << "Communicator::sendDatatransfer";

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

void Communicator::initID()
{
    uint8_t data[] = {0,0};
    serial->writeBytes(data,2);
}

