import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import Displaymaster.connectionManager 1.0

ApplicationWindow {
    visible: true
    width: 1920
    height: 1060

    title: qsTr("Hello World")
    color: "#FFFFFF"
    background: Rectangle{
        color: "#000000"
    }


    LCARSButtonPanel {
        anchors.fill: parent


    }


    LCARSMessageWindow {
        anchors.centerIn: parent
    }

    /*LCARSButton {
        id: connectButton
        text: con.connected ? "Disconnect" : "Connect"
        onClicked: {
            con.connected=!con.connected;
        }
    }

    LCARSButton {
        id: sendButton
        visible: con.connected
        anchors.top: connectButton.bottom
        anchors.topMargin: 5
        text: "Init ID"
        onClicked: {
            con.send();
        }
    }

    LCARSButton {
        id: sendTextButton
        visible: con.connected
        anchors.top: sendButton.bottom
        anchors.topMargin: 5
        text: "Send Text"
        onClicked: {
            con.sendText();
        }
    }

    Text {
        id: msg
        text: con.message
        anchors.left: connectButton.right;
    }

    Text {

        anchors.left: connectButton.right;
        anchors.top: msg.bottom
        text: "Number of displays: " + con.displayCount;
    }*/

    ConnectionManager {
        id: con
    }

}
