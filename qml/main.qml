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


    property string page: "connect"

    LCARSButtonPanel {
        id: mainPanel
        anchors.fill: parent
        header:  "System display"
        footer:  "V 0.0.1"


        buttons: [
            LCARSSiteButton {
                active: page=="connect" ? 20 : 0
                defaultWidth: mainPanel.buttonsize
                text: Con.connected ? "Disconnect" : "Connect"

                onClicked: {
                    page = "connect"
                    Con.connected=!Con.connected;
                }
            },

            LCARSSiteButton {
                active: page=="freetext" ? 20 : 0
                defaultWidth: mainPanel.buttonsize
                visible: Con.connected
                anchors.topMargin: 5
                text: "Free text"
                onClicked: {
                    page="freetext" //con.sendText();
                }
            },

            LCARSSiteButton {
                active: page=="brightness" ? 20 : 0
                defaultWidth: mainPanel.buttonsize
                visible: Con.connected
                anchors.topMargin: 5
                text: "Brightness"
                onClicked: {
                    page="brightness"
                }
            },

            LCARSSiteButton {
                active: page=="content" ? 20 : 0
                defaultWidth: mainPanel.buttonsize
                visible: true//con.connected
                anchors.topMargin: 5
                text: "Dynamic content"
                onClicked: {
                    page="content"
                }
            },

            LCARSSiteButton {
                active: page=="chareditor" ? 20 : 0
                defaultWidth: mainPanel.buttonsize
                visible: true//con.connected
                anchors.topMargin: 5
                text: "Character editor"
                onClicked: {
                    page="chareditor"
                }
            }
        ]

        contents: [
            FreeTextPanel {
                visible: page==="freetext"
            },

            ConnectPanel {
                visible: page==="connect"
            },

            BrightnessPanel {
                visible: page==="brightness"
            },

            DynamicPanel {
                visible: page==="content"
            },

            CharacterPanel {
                visible: page==="chareditor"
            }

        ]
    }

    LCARSMessageWindow {
        anchors.centerIn: parent
    }


}
