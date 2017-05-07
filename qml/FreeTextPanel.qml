import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Displaymaster.display 1.0
import Displaymaster.connectionManager 1.0

Panel {
    anchors.fill: parent
    isBlue: true

    Display {
        id: livedisplay
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 15
        height: 100
        width: 300
        rows: 4
        columns: 20
    }



    LCARSTextArea {
        id: area
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: livedisplay.bottom
        anchors.topMargin: 20
        width: 350
        height: 250
    }

    LCARSButton {
        text: "Send"

        onClicked: {
            Con.writeText(area.text)
            livedisplay.setContent(Con.framebufferContent);
        }
    }

    color: "#000000"
    //   color: "#FF00FF"
}
