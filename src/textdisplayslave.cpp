#include <QString>
#include <QDebug>

#include "textdisplayslave.h"

TextDisplaySlave::TextDisplaySlave(uint16_t id, uint16_t hw_id)
    : BasicSlave(id,hw_id)
{
    qDebug() << "Created TextDisplaySlave";
}

QString TextDisplaySlave::getName()
{
    return "TextDisplaySlave";
}
