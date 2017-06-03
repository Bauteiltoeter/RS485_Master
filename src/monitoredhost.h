#ifndef MONITOREDHOST_H
#define MONITOREDHOST_H

#include <QObject>

#include "qicmp.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class MonitoredHost : public QObject
{
    Q_OBJECT
public:
    MonitoredHost(QString hostname);
    void update();
    QStringList generateDisplay();

private slots:
    void pingFinished(int duration);
    void test(QNetworkReply* reply);
private:
    void renewDNS();
    void tryHTTP();
    QString hostname;
    QString ip;
    int ping;
    QICMP qicmp;

    QNetworkAccessManager* mgr;
};

#endif // MONITOREDHOST_H
