import QtQuick 2.0
import QtQuick.Controls 1.4
import Displaymaster.Busmaster 1.0
import Displaymaster.SlaveManager 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    onVisibleChanged: SlaveManager.loadGUI()


    Grid {
        id: slaveList
        objectName: "slaveList"

        anchors.left: parent.left
        anchors.leftMargin: 60
        anchors.top: parent.top
        anchors.topMargin: 40

        columns: 1
        spacing: 5


        ExclusiveGroup {
            id: radioInputGroup

        }




       /*    LCARSSelectableText {


                text: "fuck it"
                exclusiveGroup: radioInputGroup
            }*/





    }




    Grid {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        spacing: 5
        rows: 1

        LCARSButton {
            text: "Test slave"
            invert: true
            onClicked: {
                SlaveManager.testSlave();
            }
        }

        LCARSButton {
            text: "Ping slave"
            invert: true
            onClicked: {
                SlaveManager.pingSlave();
            }
        }

        LCARSButton {
            text: "Search slaves"
            invert: true
            onClicked: {
                Busmaster.detectSlaves();
            }
        }

        LCARSButton {
            text: "Reset ID"
            onClicked: {
                SlaveManager.resetSlaveID();
            }
        }

        LCARSButton {
            text: "Remove slave"
            onClicked: {
                SlaveManager.removeSlave();
            }
        }
    }
}
