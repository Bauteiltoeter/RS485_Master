#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <QThread>

class Communicator : public QThread
{
public:
    Communicator();
    void run();

private:
    SerialPort* serial;
};

#endif // COMMUNICATOR_H
