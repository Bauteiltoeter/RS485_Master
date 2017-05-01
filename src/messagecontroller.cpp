#include "messagecontroller.h"
#include <QDebug>

MessageController::MessageController()
{
}

MessageController::~MessageController()
{

}

MessageController *MessageController::Instance()
{
    static MessageController* singleton = new MessageController;
    return singleton;

}

void MessageController::messageBoxClosed()
{
    qDebug() << "MEssage box closed!";
    delete msgList.first();
    msgList.removeFirst();
    emit messageBoxVisibleChanged();
    emit messageChanged();
}

bool MessageController::messageBoxVisible()
{
    return !msgList.empty();
}

bool MessageController::isError()
{
    if(msgList.empty())
        return false;

    return msgList.first()->isError();
}

QString MessageController::message()
{
    if(msgList.empty())
        return "list empty";


    return msgList.first()->getText();
}

void MessageController::addMessage(Message* msg)
{
    msgList.append(msg);
    emit messageBoxVisibleChanged();
    emit messageChanged();
    emit isErrorChanged();
}
