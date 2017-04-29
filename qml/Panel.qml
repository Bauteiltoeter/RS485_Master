import QtQuick 2.0

Rectangle {
    property bool isBlue: false

    width: 400
    height: 300

    color: "#000000"
    radius: 25


    Image {
        source:isBlue ? "qrc:/images/panel_topleft_bl.svg" : "qrc:/images/panel_topleft.svg"
        anchors.left: parent.left
        anchors.top: parent.top
        height:parent.height/4.4
        width: parent.width/11
    }

    Image {
        source:isBlue ? "qrc:/images/panel_bottomleft_bl.svg" : "qrc:/images/panel_bottomleft.svg"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height:parent.height/4.4
        width: parent.width/11
    }

    Image {
        source:isBlue ? "qrc:/images/panel_bottomright_bl.svg" : "qrc:/images/panel_bottomright.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height:parent.height/4.4
        width: parent.width/11
    }

    Image {
        source:isBlue ? "qrc:/images/panel_topright_bl.svg" : "qrc:/images/panel_topright.svg"
        anchors.right: parent.right
        anchors.top: parent.top
        height:parent.height/4.4
        width: parent.width/11
    }


}
