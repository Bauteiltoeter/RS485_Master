import QtQuick 2.0
import Displaymaster.display 1.0
import Displaymaster.Busmaster 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    property string port: "/dev/ttyUSB0"


    Grid {
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

        columns: 7
        spacing: 5



        LCARSSelectableText {
          id: port1
            text: "/dev/ttyUSB0"
            checked: true
            onCheckedChanged: {
                if(checked)
                {
                    port2.checked=false;
                    port3.checked=false;
                    port4.checked=false;
                    port=text;
                }
            }
        }
        LCARSSelectableText {
          id: port2
            text: "/dev/ttyUSB1"
            onCheckedChanged: {
                if(checked)
                {
                    port1.checked=false;
                    port3.checked=false;
                    port4.checked=false;
                    port=text;
                }
            }
        }
        LCARSSelectableText {
         id: port3
            text: "/dev/ttyUSB2"
            onCheckedChanged: {
                if(checked)
                {
                    port2.checked=false;
                    port1.checked=false;
                    port4.checked=false;
                    port=text;
                }
            }
        }
        LCARSSelectableText {
         id: port4
            text: "/dev/ttyUSB3"
            onCheckedChanged: {
                if(checked)
                {
                    port2.checked=false;
                    port3.checked=false;
                    port1.checked=false;
                    port=text;
                }
            }
        }

    }

    LCARSButton {
        text: "Connect"
        anchors.centerIn: parent

        onClicked: {
            Busmaster.connect(port);
        }
    }
}
