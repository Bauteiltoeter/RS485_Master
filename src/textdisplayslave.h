#ifndef TEXTDISPLAYSLAVE_H
#define TEXTDISPLAYSLAVE_H

#include <QString>
#include "basicslave.h"


class TextDisplaySlave : public BasicSlave
{
    Q_OBJECT
public:
    TextDisplaySlave(uint16_t id, uint16_t hw_id);
    QString getName();
};

#endif // TEXTDISPLAYSLAVE_H
