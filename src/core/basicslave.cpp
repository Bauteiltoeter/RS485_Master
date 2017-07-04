#include "basicslave.h"
#include "busmaster.h"
#include <QList>
#include <QQmlComponent>
BasicSlave::BasicSlave(uint16_t id, uint16_t hw_id)
{
    this->id=id;
    this->hw_id=hw_id;
    status=Slavestatus::UNTESTED;
    qmlComponent=NULL;
}

QString BasicSlave::getName()
{
    return "BasicClass";
}

void BasicSlave::testSlave()
{
    qDebug() << "testSlave called on base class!";
}

void BasicSlave::initGUI(QQmlApplicationEngine *engine)
{
    QList<QObject*> rootObject = engine->rootObjects();

    if(!rootObject.isEmpty())
    {
        QQuickItem* grid  = rootObject.first()->findChild<QQuickItem*>("slaveList");
        QQmlComponent component(engine, QUrl("qrc:/qml/LCARSSelectableText.qml"));
        qmlComponent = qobject_cast<QQuickItem*>(component.create());
        qmlComponent->setParentItem(grid);

        qmlComponent->setProperty("text",getName() + "  ID:" + QString::number(getId()));
        qmlComponent->setProperty("color","#FF00FF");
        qmlComponent->setProperty("exclusiveGroup","radioInputGroup");


        setStatus(status);


    }
    else
    {
        qDebug() << "No root object!";
    }
}

uint16_t BasicSlave::getId()
{
    return id;
}

uint16_t BasicSlave::getHwId()
{
    return hw_id;
}

void BasicSlave::setStatus(Slavestatus::slavestatus_t status)
{
    if(qmlComponent)
    {
        switch(status)
        {
        case Slavestatus::UNTESTED: qmlComponent->setProperty("color","#FF9900"); break;
        case Slavestatus::RESPONSIVE: qmlComponent->setProperty("color","#99CCFF"); break;
        case Slavestatus::DEAD:qmlComponent->setProperty("color","#CC6699"); break;
        }
    }

    this->status=status;
}

Slavestatus::slavestatus_t BasicSlave::getStatus()
{
    return this->status;
}

bool BasicSlave::isSelected()
{
    bool tmp=false;

    if(qmlComponent)
    {
        tmp=qmlComponent->property("checked").toBool();
    }

    return tmp;
}

void BasicSlave::receiveSuccess(int t_id, uint8_t *data)
{
    if(receiveMap.contains(t_id))
    {
        receiveMap[t_id]->deserialise(data);
    }
}

void BasicSlave::sendMessage(slave_messages::msg_master_slave* msg)
{
    uint8_t* buffer;
    uint8_t length;
    msg->serialise(&buffer,&length);
    Busmaster::Instance()->transmit_master_slave(id,msg->getMsg_id(),length,buffer);
}

void BasicSlave::requestMessage(slave_messages::msg_slave_master *msg)
{
    if(!signalsConnected)
    {
        qDebug() << "Connecting signals vom BasicSlave to Busmaster";
        signalsConnected=true;

        connect(Busmaster::Instance(),SIGNAL(receiveSuccess(int,uint8_t*)),this,SLOT(receiveSuccess(int,uint8_t*)));
    }

    int t_id = Busmaster::Instance()->transmit_slave_master(id, msg->getMsg_id(),msg->getLength());

    receiveMap[t_id] = msg;
}
