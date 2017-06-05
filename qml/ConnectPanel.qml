import QtQuick 2.0
import Displaymaster.display 1.0
import Displaymaster.Busmaster 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    Grid {
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 80

        columns: 7
spacing: 5

        Repeater {
            model: 25*7


            LCARSSelectableText {
              //  color: "#FFFF00"
                text: "/dev/ttydasdfasdfa"
            }
        }







    }

    LCARSButton {
        text: "Connect"
        anchors.centerIn: parent

        onClicked: {
            Busmaster.connect();
        }
    }
}
