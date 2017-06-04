#include "slavemanager.h"
#include "basicslave.h"
#include "textdisplayslave.h"
#include "message.h"
#include "messagecontroller.h"
#include <QFile>
#include <QDebug>

typedef enum  {
    TEXTDISPLAY = 2
}slave_hw_t;

SlaveManager::SlaveManager()
{
    slave_filename = "slaves.xml";

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

QString SlaveManager::slaveNames()
{
    QString names="";

    foreach(auto slave, knownSlaves)
    {
        names.append(""+ QString::number(slave->getId()) + ": " + slave->getName()) +"\n\n";
    }

    return names;
}

void SlaveManager::loadSlaves(QString filename)
{
    QFile xmlFile(filename);
      xmlFile.open(QIODevice::ReadOnly);
      xml.setDevice(&xmlFile);

      if (xml.readNextStartElement() && xml.name() == "slaves")
         processSlaves();

      // readNextStartElement() leaves the stream in
      // an invalid state at the end. A single readNext()
      // will advance us to EndDocument.
      if (xml.tokenType() == QXmlStreamReader::Invalid)
          xml.readNext();

      if (xml.hasError()) {
          xml.raiseError();
         // qDebug() << errorString();
      }


}

void SlaveManager::saveSlaves(QString filename)
{
    QFile file(filename);

    file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);

     QTextStream stream( &file );

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
