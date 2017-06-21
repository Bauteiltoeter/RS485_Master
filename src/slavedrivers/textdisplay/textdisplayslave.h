#ifndef TEXTDISPLAYSLAVE_H
#define TEXTDISPLAYSLAVE_H

#include <QString>
#include <QQmlApplicationEngine>
#include "basicslave.h"

namespace slave_messages
{

    class msg_complete_update_t : public msg_master_slave
    {
    public:
        msg_complete_update_t() { msg_id=2;}
        void serialise(uint8_t** buffer, uint8_t* length);

        char characters[4*20];
        uint32_t dots[4];
    };

    class msg_brightness_t : public msg_master_slave
    {
    public:
        msg_brightness_t() { msg_id=3;}
        void serialise(uint8_t** buffer, uint8_t* length);

        uint8_t autocontrol;
        uint16_t brightness;
        uint8_t x2;
        uint8_t x1;
        uint8_t x0;
    };
}

class TextDisplaySlave : public BasicSlave
{
    Q_OBJECT
public:
    TextDisplaySlave(uint16_t id, uint16_t hw_id);
    QString getName();
};

#endif // TEXTDISPLAYSLAVE_H
