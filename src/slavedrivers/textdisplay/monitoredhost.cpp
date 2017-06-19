#include "monitoredhost.h"
#include <QHostInfo>
#include <QSsl>
#include <QNetworkRequest>
#include <QEventLoop>

MonitoredHost::MonitoredHost(QString hostname)
{
    this->hostname = hostname;
    renewDNS();
    connect(&qicmp,SIGNAL(pingFinished(int)),this,SLOT(pingFinished(int)));
    ping = -1;
}

void MonitoredHost::update()
{
    renewDNS();
    tryHTTP();

    if(ip!="")
    {
        //qicmp.setIP(ip);
        //qicmp.ping();

        //tryHTTP();
    }
    else
    {
        qDebug() << "No IP adress";
    }
}

QStringList MonitoredHost::generateDisplay()
{
    QStringList tmp;

    tmp.append(hostname);

    if(ip=="")
    {
        tmp.append("DNS Error");
        tmp.append("");
    }
    else
    {
        tmp.append(ip);


        if(ping<0)
            tmp.append("ICMP Error");
        else
            tmp.append("Ping " +  QString::number(ping)+"ms");

    }
    return tmp;
}

void MonitoredHost::pingFinished(int duration)
{
    ping=duration;
}

void MonitoredHost::test(QNetworkReply* reply)
{
    qDebug() << "MonitoredHost::test()";
    if (reply->error() == QNetworkReply::NoError) {
            //success
            qDebug() << "Success" <<reply->readAll();
        //delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
      //  delete reply;
    }
}

void MonitoredHost::renewDNS()
{
    QHostInfo info = QHostInfo::fromName(hostname);
    auto adresslist =  info.addresses();

   // qDebug() << adresslist;
    ip="";
    for(int i=0; i < adresslist.size(); i++)
    {
        if(adresslist[i].toString().length()<=15)
            ip=adresslist[i].toString();
    }

    // ip = info.addresses()[0].
}

void MonitoredHost::tryHTTP()
{
    // create custom temporary event loop on stack
   // QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"

    //QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    mgr = new QNetworkAccessManager();

    QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(test(QNetworkReply*)));
    // the HTTP request
    QNetworkRequest req( QUrl( QString("http://tortronik.de/") ) );
    QNetworkReply *reply = mgr->head(req);
 //   eventLoop.exec(); // blocks stack until "finished()" has been called

   /* if (reply->error() == QNetworkReply::NoError) {
        //success
        qDebug() << "Success" <<reply->readAll();
        delete reply;
    }
    else {
        //failure
        qDebug() << "Failure" <<reply->errorString();
        delete reply;
    }*/

}

