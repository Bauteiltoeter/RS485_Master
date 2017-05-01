import QtQuick 2.0
import Displaymaster.messageController 1.0

Panel {
    visible: MessageController.messageBoxVisible

    isBlue: !MessageController.isError

    LCARSText {
        id: headertext
        text: MessageController.isError ? "Error" : "Info"
        color: MessageController.isError ? "#ff3232" : "#9999ff"
        font.pixelSize: 50
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
    }

    LCARSText {
        text: MessageController.message
        color: MessageController.isError ? "#ff3232" : "#9999ff"
        font.pixelSize: 30
        anchors.centerIn: parent
    }

    LCARSButton {
        text: "OK"
        invert: !MessageController.isError
        onClicked: {
            MessageController.messageBoxClosed();
        }
    }




}
