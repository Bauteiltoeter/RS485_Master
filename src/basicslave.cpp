#include "basicslave.h"

BasicSlave::BasicSlave(uint16_t id, uint16_t hw_id)
{
    this->id=id;
    this->hw_id=hw_id;
}

QString BasicSlave::getName()
{
    return "BasicClass";
}

uint16_t BasicSlave::getId()
{
    return id;
}
