#ifndef QICMP_H
#define QICMP_H

#include <QObject>
#include <QThread>
#include <QString>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <sys/select.h>


class QICMP : public QThread
{
    Q_OBJECT
public:
    QICMP();
    void setIP(QString ip);
    void ping();

signals:
    void pingFinished(int duration);

private:
    void run();

    struct in_addr server_ip;
};

#endif // QICMP_H
