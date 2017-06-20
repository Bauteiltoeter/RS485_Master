#include <QString>
#include <QDebug>

#include "powermeterslave.h"

PowerMeterSlave::PowerMeterSlave(uint16_t id, uint16_t hw_id)
    : BasicSlave(id,hw_id)
{
    qDebug() << "Created TextDisplaySlave";
}

QString PowerMeterSlave::getName()
{
    return "PowerMeterSlave";
}

/*
void TextDisplaySlave::msg_complete_update_serialiser(textdisplayslave_messages::msg_complete_update_t* msg, uint8_t** buffer, uint8_t* length)
{
    uint8_t msg_length = 80+4*4;
    *length=msg_length;

    *buffer= new uint8_t[msg_length];

    memcpy(buffer,msg->characters,80);
    for(int i=0; i < 4; i++)
    {
        *buffer[80+ i*4 + 0] = (uint8_t)msg->dots[i]>>24;
        *buffer[80+ i*4 + 1] = (uint8_t)msg->dots[i]>>16;
        *buffer[80+ i*4 + 2] = (uint8_t)msg->dots[i]>>8;
        *buffer[80+ i*4 + 3] = (uint8_t)msg->dots[i]>>0;
    }
}

void TextDisplaySlave::msg_brightness_serialiser(textdisplayslave_messages::msg_brightness_t *msg, uint8_t** buffer, uint8_t* length)
{
    uint8_t msg_length = 6;
    *length=msg_length;

    *buffer= new uint8_t[msg_length];

    *buffer[0] = msg->autocontrol;
    *buffer[1] = msg->brightness>>8;
    *buffer[2] = msg->brightness;
    *buffer[3] = msg->x2;
    *buffer[4] = msg->x1;
    *buffer[5] = msg->x0;
}
*/
