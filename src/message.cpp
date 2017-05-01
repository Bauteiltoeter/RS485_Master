#include "message.h"

Message::Message(bool error, QString text)
{
    _error = error;
    _text = text;
}

QString Message::getText()
{
    return _text;
}

bool Message::isError()
{
    return _error;
}
