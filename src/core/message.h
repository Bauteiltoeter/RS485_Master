#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message(bool error, QString text);
    QString getText();
    bool isError();

private:
    QString _text;
    bool _error;
};

#endif // MESSAGE_H
