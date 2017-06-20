#include "contentpowermeter.h"
#include <QDebug>
#include <QDateTime>

ContentPowermeter::ContentPowermeter(int id, QQmlApplicationEngine* qmlEngine)
    : ContentBasic(id,qmlEngine)
{
    createGUI("qrc:/qml/ContentPowermeter.qml");


}

QString ContentPowermeter::name()
{
    return "Power meter";
}

void ContentPowermeter::run()
{

}

QString ContentPowermeter::headerText()
{
    return "3-Phase power measurement";
}

QString ContentPowermeter::footerText()
{
    return "";
}
