#include "slavemanager.h"
#include "basicslave.h"
#include "textdisplayslave.h"
#include "powermeterslave.h"
#include "message.h"
#include "messagecontroller.h"
#include "busmaster.h"
#include <QFile>
#include <QDebug>

typedef enum  {
    TEXTDISPLAY = 2,
    POWERMETER =3
}slave_hw_t;

SlaveManager::SlaveManager()
{
    slave_filename = "slaves.xml";
    qmlEngine=NULL;

    loadSlaves(slave_filename);
}

SlaveManager* SlaveManager::Instance()
{
    static SlaveManager* sm = new SlaveManager();
    return sm;
}

void SlaveManager::createSlave(uint16_t id, uint16_t hw_id)
{
    BasicSlave* newSlave;

    switch(hw_id)
    {
        case TEXTDISPLAY: newSlave = new TextDisplaySlave(id,hw_id); break;
        case POWERMETER:  newSlave = new PowerMeterSlave(id,hw_id); break;
        default: MessageController::Instance()->addMessage(new Message(true,"Unknown hardware")); break;
    }

    if(newSlave)
    {
        qDebug() << "Added slave to list";
        knownSlaves.append(newSlave);
        emit slaveNamesChanged();
        saveSlaves(slave_filename);
    }
}

void SlaveManager::connected()
{
    qDebug() << "Pinging all slaves";
    connect(Busmaster::Instance(),SIGNAL(transmitError(int)),this,SLOT(transmitError(int)));
    connect(Busmaster::Instance(),SIGNAL(transmitSuccess(int)),this,SLOT(transmitSuccess(int)));

    foreach(BasicSlave* slave, knownSlaves)
    {
        uint16_t t_id = Busmaster::Instance()->pingSlave(slave->getId());

        pingMap[t_id] = slave;
    }
}

QString SlaveManager::slaveNames()
{
    QString names="";

    foreach(auto slave, knownSlaves)
    {
        names.append(""+ QString::number(slave->getId()) + ": " + slave->getName()) +"\n\n";
    }

    return names;
}

void SlaveManager::setQmlEngine(QQmlApplicationEngine *engine)
{
    this->qmlEngine=engine;

}

uint16_t SlaveManager::getNextFreeId()
{
    uint16_t tmp = nextFreeId;
    nextFreeId++;
    return tmp;
}

void SlaveManager::loadGUI()
{
    static bool loaded=false;

    if(qmlEngine && !loaded)
    {
        foreach(BasicSlave* slave, knownSlaves)
        {
            slave->initGUI(qmlEngine);
        }

        if(!qmlEngine->rootObjects().isEmpty())
            loaded=true;
    }
}

void SlaveManager::pingSlave()
{
    BasicSlave* selected = getSelected();

    if(selected)
    {

        int t_id = Busmaster::Instance()->pingSlave(selected->getId());
        pingMap[t_id]=selected;
    }
    else
    {
        qDebug() << "Nothing selected";
    }
}

void SlaveManager::resetSlaveID()
{

}

void SlaveManager::removeSlave()
{

}

BasicSlave *SlaveManager::getSelected()
{
    foreach(BasicSlave* slave, knownSlaves)
    {
        if(slave->isSelected())
            return slave;
    }
    return NULL;
}

void SlaveManager::transmitSuccess(int t_id)
{
    BasicSlave* t = pingMap[t_id];

    if(t)
    {
        t->setStatus(Slavestatus::RESPONSIVE);
        qDebug() << "TransmitSuccess: " << t_id << t  ->getName();
    }
}

void SlaveManager::transmitError(int t_id)
{

    BasicSlave* t = pingMap[t_id];

    if(t)
    {
        t->setStatus(Slavestatus::DEAD);
        MessageController::Instance()->addMessage(new Message(true,"Slave not responding\n"+ t->getName() +" ID:" + QString::number(t->getId())));
        qDebug() << "TransmitError: " << t_id << t  ->getName();
    }
}

void SlaveManager::loadSlaves(QString filename)
{
    qDebug() << "loading Slaves";

    QFile xmlFile(filename);
    xmlFile.open(QIODevice::ReadOnly);
    xml.setDevice(&xmlFile);


    while (xml.readNextStartElement())
    {
        if (xml.name() == "slaves")
            processSlaves();
        else if(xml.name() == "nextId")
        {
            nextFreeId = readNextText().toInt();
        }
    }



    // readNextStartElement() leaves the stream in
    // an invalid state at the end. A single readNext()
    // will advance us to EndDocument.
    if (xml.tokenType() == QXmlStreamReader::Invalid)
        xml.readNext();

    if (xml.hasError())
    {
        xml.raiseError();
        // qDebug() << errorString();
    }
}

void SlaveManager::saveSlaves(QString filename)
{
    QFile file(filename);

    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

     QTextStream stream( &file );

     stream << "<nextId>\n  "<<nextFreeId<<"\n</nextId>";

     stream << "<slaves>\n";

     foreach(auto slave, knownSlaves)
     {

         stream << " <slave>\n  <id>" << QString::number(slave->getId()) << "</id>\n  <hw>" << QString::number(slave->getHwId()) << "</hw>\n </slave>\n";


         //names.append(""+ QString::number(slave->getId()) + ": " + slave->getName()) +"\n\n";
     }

     stream << "</slaves>";
    file.close();
}

void SlaveManager::processSlaves()
{
    qDebug() << "reading slave";
    if (!xml.isStartElement() || xml.name() != "slaves")
        return;
    while (xml.readNextStartElement())
    {
        if (xml.name() == "slave")
            processSlave();
        else
            xml.skipCurrentElement();
    }
}

void SlaveManager::processSlave()
{
    if (!xml.isStartElement() || xml.name() != "slave")
    return;

    QString id;
    QString hw_id;
    while (xml.readNextStartElement())
    {
        if (xml.name() == "id")
            id = readNextText();
        else if (xml.name() == "hw")
            hw_id = readNextText();
#ifndef USE_READ_ELEMENT_TEXT
        xml.skipCurrentElement();
#endif
    }

    qDebug() << "Read slave with id: " << id << " hw: " << hw_id;
    createSlave(id.toInt(),hw_id.toInt());
}

QString SlaveManager::readNextText() {
#ifndef USE_READ_ELEMENT_TEXT
    xml.readNext();
    return xml.text().toString();
#else
    return xml.readElementText();
#endif
}
