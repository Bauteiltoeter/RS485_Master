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
    slave_messages::msg_complete_update_t tmp;
    memset(tmp.characters,0,80);
    strncpy(tmp.characters, "Hallo Welt!",80);
    tmp.dots[0] = 0x01234567;
    tmp.dots[1] = 0x89ABCDEF;
    tmp.dots[2] = 0x01234567;
    tmp.dots[3] = 0x89ABCDEF;
    sendMessage(&tmp);

    return "TextDisplaySlave";
}


void slave_messages::msg_complete_update_t::serialise(uint8_t** buffer, uint8_t* length)
{
    uint8_t msg_length = 80+4*4;
    *length=msg_length;

    uint8_t *tmp= new uint8_t[msg_length];

    memcpy(tmp,characters,80);
    for(int i=0; i < 4; i++)
    {
        tmp[80+ i*4 + 0] = dots[i]>>24;
        tmp[80+ i*4 + 1] = dots[i]>>16;
        tmp[80+ i*4 + 2] = dots[i]>>8;
        tmp[80+ i*4 + 3] = dots[i]>>0;
    }
    *buffer=tmp;
}

void slave_messages::msg_brightness_t::serialise(uint8_t** buffer, uint8_t* length)
{
    uint8_t msg_length = 6;
    *length=msg_length;

    *buffer= new uint8_t[msg_length];

    *buffer[0] = autocontrol;
    *buffer[1] = brightness>>8;
    *buffer[2] = brightness;
    *buffer[3] = x2;
    *buffer[4] = x1;
    *buffer[5] = x0;
}
