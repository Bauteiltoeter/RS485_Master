#ifndef BASICSLAVE_H
#define BASICSLAVE_H

#include <QObject>

class BasicSlave : public QObject
{
    Q_OBJECT
public:
    BasicSlave(uint16_t id, uint16_t hw_id);
    virtual QString getName();

    uint16_t getId();
    uint16_t getHwId();

private:
    uint16_t id;
    uint16_t hw_id;
};

#endif // BASICSLAVE_H
