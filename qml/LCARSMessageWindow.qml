import QtQuick 2.0
import Displaymaster.messageController 1.0

Panel {
    property string header: "Error"
    visible: MessageController.messageBoxVisible

    LCARSText {
        id: headertext
        text: header
        color: "#ff3232"
        font.pixelSize: 50
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
    }

    LCARSText {
        text: MessageController.message
        color: "#ff3232"
        font.pixelSize: 30
        anchors.centerIn: parent
    }

    LCARSButton {
        text: "OK"

        onClicked: {
            MessageController.messageBoxClosed();
        }
    }




}
