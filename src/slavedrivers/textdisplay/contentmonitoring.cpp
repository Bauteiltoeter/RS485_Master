#include "contentmonitoring.h"



ContentMonitoring::ContentMonitoring(int id, QQmlApplicationEngine* qmlEngine)
    : ContentBasic(id,qmlEngine)
{
    createGUI("qrc:/qml/ContentMonitoring.qml");

    hostList.append(new MonitoredHost("tortronik.de"));
  //  hostList.append(new MonitoredHost("acis-ingolstadt.de"));
  //  hostList.append(new MonitoredHost("fingers-welt.de"));
   // hostList.append(new MonitoredHost("fasdfas.de"));
}

QString ContentMonitoring::name()
{
    return "Monitoring";
}

void ContentMonitoring::run()
{
    static int i=0;
    static int current_index=0;
    i++;

    if(i==25)
    {
        foreach(auto host, hostList)
            host->update();
    }

    if(i==50)
    {
        QStringList tmp = hostList[current_index]->generateDisplay();

        qDebug() << "generateDisplay:" << tmp;
        emit requestStringTransmit(contentID,tmp);
       // qicmp->ping();
        i=0;
        current_index++;

        if(current_index>=hostList.size())
            current_index=0;
    }



}
