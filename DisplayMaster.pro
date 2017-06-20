QT += qml quick widgets

CONFIG += c++11

SOURCES += src/main.cpp \
    src/slavedrivers/textdisplay/displayConnection.cpp \
    src/core/serialport.cpp \
    src/core/messagecontroller.cpp \
    src/core/message.cpp \
    src/slavedrivers/textdisplay/segmentdisplay.cpp \
    src/slavedrivers/textdisplay/display.cpp \
    src/slavedrivers/textdisplay/contentmanager.cpp \
    src/slavedrivers/textdisplay/contentbasic.cpp \
    src/slavedrivers/textdisplay/contentFreetext.cpp \
    src/slavedrivers/textdisplay/contentclock.cpp \
    src/slavedrivers/textdisplay/contentfinger.cpp \
    src/slavedrivers/textdisplay/contentmonitoring.cpp \
    src/slavedrivers/textdisplay/contentpowermeter.cpp \
    src/slavedrivers/textdisplay/qicmp.cpp \
    src/slavedrivers/textdisplay/monitoredhost.cpp \
    src/core/busmaster.cpp \
    src/core/slavemanager.cpp \
    src/core/basicslave.cpp \
    src/slavedrivers/textdisplay/textdisplayslave.cpp \
    src/slavedrivers/powermeter/powermeterslave.cpp

RESOURCES += qml.qrc \
		images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += src src/core/ src/slavedrivers/textdisplay/ src/slavedrivers/powermeter
HEADERS += \
    src/core/serialport.h \
    src/core/messagecontroller.h \
    src/slavedrivers/textdisplay/displayConnection.h \
    src/core/message.h \
    src/slavedrivers/textdisplay/segmentdisplay.h \
    src/slavedrivers/textdisplay/display.h \
    src/slavedrivers/textdisplay/communicator.h \
    src/slavedrivers/textdisplay/contentmanager.h \
    src/slavedrivers/textdisplay/contentbasic.h \
    src/slavedrivers/textdisplay/contentFreetext.h \
    src/slavedrivers/textdisplay/contentclock.h \
    src/slavedrivers/textdisplay/contentfinger.h \
    src/slavedrivers/textdisplay/contentmonitoring.h \
    src/slavedrivers/textdisplay/contentpowermeter.h \
    src/slavedrivers/textdisplay/qicmp.h \
    src/slavedrivers/textdisplay/monitoredhost.h \
    src/core/busmaster.h \
    src/core/slavemanager.h \
    src/core/basicslave.h \
    src/slavedrivers/textdisplay/textdisplayslave.h \
    src/slavedrivers/powermeter/powermeterslave.h
