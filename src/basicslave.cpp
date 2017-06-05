#include "basicslave.h"
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
