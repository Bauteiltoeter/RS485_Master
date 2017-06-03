import QtQuick 2.0

Panel {
    property alias text: msgText.text
    property bool invert: false
    signal clicked;

    width: 200
    height: 50
 //   anchors.bottom: parent.bottom
 //   anchors.bottomMargin: 15
 //   anchors.horizontalCenter: parent.horizontalCenter
    isBlue: invert ? !clickArea.pressed : clickArea.pressed

    LCARSText {
        id: msgText
        anchors.centerIn: parent
        color: clickArea.pressed?  (invert ? "#ff3232" :  "#9999ff") : (invert ? "#9999ff" : "#ff3232")
        font.pixelSize: 35

    }

    MouseArea {
        id: clickArea
        anchors.fill: parent

        onClicked: {
            parent.clicked();
        }
    }
}
