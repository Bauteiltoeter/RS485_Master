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

void TextDisplaySlave::testSlave()
{
    slave_messages::msg_info_t* t = new slave_messages::msg_info_t();
    requestMessage(t);

    slave_messages::msg_complete_update_t tmp;
    memset(tmp.characters,0,80);
    strncpy(tmp.characters, "Displaytest! abcdefg"
                            "hijklmnopqrstuvwxyz0"
                            "123456789abcdefghijk"
                            "lmnkopqrstuvwxyz0123",80);
    tmp.dots[0] = 0;
    tmp.dots[1] = 0;
    tmp.dots[2] = 0;
    tmp.dots[3] = 0;
    sendMessage(&tmp);

}

/*
 *

    */

/*
void TextDisplaySlave::test()
{
    qDebug() << "TextDislaySlave test!";
    slave_messages::msg_complete_update_t tmp;
    memset(tmp.characters,0,80);
    strncpy(tmp.characters, "Hallo Welt! THIS IS A ROFLCOPTER",80);
    tmp.dots[0] = 0x01234567;
    tmp.dots[1] = 0x89ABCDEF;
    tmp.dots[2] = 0x01234567;
    tmp.dots[3] = 0x89ABCDEF;
    sendMessage(&tmp);
}*/


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
    uint8_t msg_length = 7;
    *length=msg_length;

    uint8_t *tmp = new uint8_t[msg_length];

    tmp[0] = on_off;
    tmp[1] = autocontrol;
    tmp[2] = brightness>>8;
    tmp[3] = brightness;
    tmp[4] = x2;
    tmp[5] = x1;
    tmp[6] = x0;

    *buffer=tmp;
}

void slave_messages::msg_info_t::deserialise(uint8_t *buffer)
{
    rows = buffer[0];
    columns = buffer[1];
    qDebug() << "deserialised msg_info_t: " << rows << "; " << columns;

    delete buffer;
}
