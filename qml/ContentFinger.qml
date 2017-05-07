import QtQuick 2.0

Panel {
    anchors.fill: parent
    isBlue: true

    signal send

    LCARSText {
        id: txt
        text: "FINGER"
        color: "#FFFF00"
        font.pixelSize: 100
        anchors.centerIn: parent;
    }

    LCARSButton {
        text: "Send"
        anchors.top: txt.bottom
        onClicked: {

           parent.send();
        }
    }
}
