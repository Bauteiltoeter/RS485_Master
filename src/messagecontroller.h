#ifndef MESSAGECONTROLLER_H
#define MESSAGECONTROLLER_H


#include <QObject>
#include <QString>
#include <QStringList>
#include "message.h"

class MessageController : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool messageBoxVisible READ messageBoxVisible NOTIFY messageBoxVisibleChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(bool isError READ isError NOTIFY isErrorChanged)

public:
    MessageController();
    ~MessageController();

    static MessageController* Instance();

    bool messageBoxVisible();
    bool isError();
    void addMessage(Message* msg);
    QString message();

public slots:
    void messageBoxClosed();

signals:
    void messageBoxVisibleChanged();
    void messageChanged();
    void isErrorChanged();

private:
    QList<Message*> msgList;


};


#endif // MESSAGECONTROLLER_H
