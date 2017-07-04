#ifndef BASICSLAVE_H
#define BASICSLAVE_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>
#include <QMap>

namespace Slavestatus
{
    typedef enum {
        UNTESTED,
        RESPONSIVE,
        DEAD
    } slavestatus_t;
}

namespace slave_messages
{
    class msg_master_slave
    {
    protected: uint16_t msg_id;
       public:
       uint16_t getMsg_id() { return msg_id;}
       virtual void serialise(uint8_t** buffer, uint8_t* length)=0;
    };

    class msg_slave_master
    {
    protected: uint16_t msg_id;
               uint8_t length;
       public:
       uint16_t getMsg_id() { return msg_id;}
       uint8_t getLength() { return length;}
       virtual void deserialise(uint8_t* buffer)=0;
    };
}

class BasicSlave : public QObject
{
    Q_OBJECT
public:
    BasicSlave(uint16_t id, uint16_t hw_id);
    virtual QString getName();
    virtual void testSlave();

    void initGUI(QQmlApplicationEngine* engine);
    uint16_t getId();
    uint16_t getHwId();
    void setStatus(Slavestatus::slavestatus_t status);
    Slavestatus::slavestatus_t getStatus();
    bool isSelected();

private slots:
    void receiveSuccess(int t_id, uint8_t* data);

protected:
    void sendMessage(slave_messages::msg_master_slave* msg);
    void requestMessage(slave_messages::msg_slave_master* msg);

    uint16_t id;
    uint16_t hw_id;
    Slavestatus::slavestatus_t status;
    QQuickItem *qmlComponent;
    QMap<int, slave_messages::msg_slave_master*> receiveMap;

private:
    bool signalsConnected;
};

#endif // BASICSLAVE_H
