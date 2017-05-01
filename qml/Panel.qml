import QtQuick 2.0

Rectangle {
    property bool isBlue: false
    id: body
    width: 400
    height: 300

    color: "#000000"
    radius: 25

    function calcHeight() {
        var height = body.height/4.4

        if(height>70)
            height=70;

        return height;
    }

    function calcWidth() {
        var width = body.width/11;

        if(width>38)
            width = 38;

        return width;
    }

    Image {
        source:isBlue ? "qrc:/images/panel_topleft_bl.svg" : "qrc:/images/panel_topleft.svg"
        anchors.left: parent.left
        anchors.top: parent.top
        height:calcHeight()
        width:calcWidth()

    }

    Image {
        source:isBlue ? "qrc:/images/panel_bottomleft_bl.svg" : "qrc:/images/panel_bottomleft.svg"
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        height:calcHeight()
        width:calcWidth()
    }

    Image {
        source:isBlue ? "qrc:/images/panel_bottomright_bl.svg" : "qrc:/images/panel_bottomright.svg"
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height:calcHeight()
        width:calcWidth()
    }

    Image {
        source:isBlue ? "qrc:/images/panel_topright_bl.svg" : "qrc:/images/panel_topright.svg"
        anchors.right: parent.right
        anchors.top: parent.top
        height:calcHeight()
        width:calcWidth()
    }


}
