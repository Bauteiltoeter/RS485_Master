#include "displayConnection.h"
#include <QDebug>
#include "messagecontroller.h"
DisplayConnection::DisplayConnection(QObject *parent) : QObject(parent)
{
    numberOfDisplays=-1;
    memset(framebuffer,0,sizeof(framebuffer));


}

DisplayConnection::~DisplayConnection()
{

}

DisplayConnection *DisplayConnection::Instance()
{
    static DisplayConnection* con = new DisplayConnection;
    return con;
}

void DisplayConnection::setConnected(bool c)
{
}

bool DisplayConnection::connected()
{

}

void DisplayConnection::connectionStatusChanged()
{
    emit connectedChanged();
}




void DisplayConnection::syncFramebuffer()
{

}

void DisplayConnection::writeText(QStringList strings)
{



  //  syncFramebuffer();
}

void DisplayConnection::writeText(QString line1, QString line2, QString line3, QString line4)
{

}

void DisplayConnection::writeText(QString text)
{
    QStringList tmp = text.split('\n');
    writeText(tmp);
}

void DisplayConnection::setBrightness(double value)
{

}

QByteArray DisplayConnection::framebufferContent()
{

}






void DisplayConnection::sendDisplayText(int id, char* text)
{
}

int DisplayConnection::displayCount()
{
    return numberOfDisplays;
}

void DisplayConnection::connectionSuccess()
{

   MessageController::Instance()->addMessage(new Message(false,"Connected"));

}

void DisplayConnection::connectionError(QString msg)
{
    qDebug() << "Connection error: " << msg;

    MessageController::Instance()->addMessage(new Message(true,msg));

}


