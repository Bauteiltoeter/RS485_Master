import QtQuick 2.0
import Displaymaster.display 1.0
import Displaymaster.Busmaster 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    LCARSButton {
        text: "Search slaves"
        anchors.centerIn: parent

        onClicked: {
            Busmaster.detectSlaves();
        }
    }
}
