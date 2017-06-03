import QtQuick 2.4
import QtQuick.Controls 1.4

Panel {
    isBlue: true
    width: 800

    LCARSText {
        text: "Hosts"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        font.pixelSize: 30
        color: "#FF9900"
    }



    Grid {
        anchors.centerIn: parent

        columns: 4
        spacing: 10
        verticalItemAlignment: Grid.AlignVCenter
        LCARSText {
            text: "Host:"
            color: "#FF9900"
            font.pixelSize: 25
        }
        LCARSTextField {
            text: "tortronik.de"

            font.pixelSize: 25
        }

        ComboBox {
            model: ["ICMP","HTTP","ICMP+HTTP"]
            width: 130
        }

        LCARSButton {
            text: "Delete"
            width: 150
            height: 30
        }
    }




}
