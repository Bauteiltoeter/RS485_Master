import QtQuick 2.0
import Displaymaster.Busmaster 1.0
import Displaymaster.SlaveManager 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    LCARSText {
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.top: parent.top
        anchors.topMargin: 40
        color: "#FFFF00"
        text: SlaveManager.slaveNames
    }



    LCARSButton {
        text: "Search slaves"
        anchors.centerIn: parent

        onClicked: {
            Busmaster.detectSlaves();
        }
    }
}
