#ifndef POWERMETERSLAVE_H
#define POWERMETERSLAVE_H

#include <QString>
#include <QQmlApplicationEngine>
#include "basicslave.h"

namespace powermeterslave_messages
{

   /* typedef struct
    {
        uint8_t characters[4*20];
        uint32_t dots[4];
    } msg_complete_update_t;

    typedef struct
    {
        uint8_t autocontrol;
        uint16_t brightness;
        uint8_t x2;
        uint8_t x1;
        uint8_t x0;
    } msg_brightness_t;*/
}

class PowerMeterSlave : public BasicSlave
{
    Q_OBJECT
public:
    PowerMeterSlave(uint16_t id, uint16_t hw_id);
    QString getName();

private:
   // void msg_complete_update_serialiser(textdisplayslave_messages::msg_complete_update_t* msg, uint8_t** buffer, uint8_t* length);
   // void msg_brightness_serialiser(textdisplayslave_messages::msg_brightness_t* msg, uint8_t** buffer, uint8_t* length);

};

#endif // POWERMETERSLAVE_H
