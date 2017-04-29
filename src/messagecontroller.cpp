#include "messagecontroller.h"
#include <QDebug>

MessageController::MessageController()
{
}

void MessageController::messageBoxClosed()
{
    qDebug() << "MEssage box closed!";
    msgList.removeFirst();
    emit messageBoxVisibleChanged();
    emit messageChanged();
}

bool MessageController::messageBoxVisible()
{
    return !msgList.empty();
}

QString MessageController::message()
{
    if(msgList.empty())
        return "list empty";

    return msgList.first();
}

void MessageController::addMessage(QString msg)
{
    msgList.append(msg);
    emit messageBoxVisibleChanged();
    emit messageChanged();
}
