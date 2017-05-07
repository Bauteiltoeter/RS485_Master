#include "connection.h"
#include <QDebug>
#include <termios.h>
#include "messagecontroller.h"
connection::connection(QObject *parent) : QObject(parent)
{
    numberOfDisplays=-1;
    memset(framebuffer,0,sizeof(framebuffer));

    connect(&communicator,SIGNAL(serialSuccess()),this,SLOT(connectionSuccess()));
    connect(&communicator,SIGNAL(serialError(QString)),this,SLOT(connectionError(QString)));
    connect(&communicator,SIGNAL(connectionStatusChanged()),this,SLOT(connectionStatusChanged()));
    communicator.start();
}

connection::~connection()
{

}

connection *connection::Instance()
{
    static connection* con = new connection;
    return con;
}

void connection::setConnected(bool c)
{
    if(c)
    {
        communicator.serialConnect();
    }
    else
    {
        communicator.serialDisconnect();
    }
}

bool connection::connected()
{
    return communicator.isConnected();
}

void connection::connectionStatusChanged()
{
    emit connectedChanged();
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
    {
        Communicator::package_t* package = communicator.getNewPackage();

        package->id = i;
        package->data = &buffer;
        package->length = 1;
        package->mode = Communicator::brightness_update;

        communicator.sendPackage(package);


       // sendDatatransfer(i,brightness_update,&buffer,1);

    }
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
    return tmp;
}






void connection::sendDisplayText(int id, char* text)
{
    uint8_t* buffer = new uint8_t[20];
    memcpy(buffer,text,20);

    Communicator::package_t* package = communicator.getNewPackage();

    package->id = id;
    package->data = buffer;
    package->length = 20;
    package->mode = Communicator::character_update;

    communicator.sendPackage(package);
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


