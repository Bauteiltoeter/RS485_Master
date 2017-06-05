#ifndef BASICSLAVE_H
#define BASICSLAVE_H

#include <QObject>
#include <QQuickItem>
#include <QQmlApplicationEngine>

namespace Slavestatus
{
    typedef enum {
        UNTESTED,
        RESPONSIVE,
        DEAD
    } slavestatus_t;
}

class BasicSlave : public QObject
{
    Q_OBJECT
public:
    BasicSlave(uint16_t id, uint16_t hw_id);
    virtual QString getName();

    void initGUI(QQmlApplicationEngine* engine);
    uint16_t getId();
    uint16_t getHwId();
    void setStatus(Slavestatus::slavestatus_t status);
    Slavestatus::slavestatus_t getStatus();
    bool isSelected();

private:
    uint16_t id;
    uint16_t hw_id;
    Slavestatus::slavestatus_t status;
    QQuickItem *qmlComponent;
};

#endif // BASICSLAVE_H
