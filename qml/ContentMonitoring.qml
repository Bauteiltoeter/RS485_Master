import QtQuick 2.0

Panel {
    anchors.fill: parent
    isBlue: true

    Grid {
        anchors.centerIn: parent

        columns: 2
        spacing: 10

        LCARSText {
            text: "Monitoring"
            color: "#FFFF00"
            font.pixelSize: 25
        }
        LCARSTextField {
            text: "logic-craft.de"

            font.pixelSize: 25
        }
        LCARSText {
            text: "Monitoring"
            color: "#FFFF00"
            font.pixelSize: 25

        }
        LCARSTextField {
            text: "acis-ingolstadt.de"

            font.pixelSize: 25
        }
    }


}
