import QtQuick 2.0


Item {


    anchors.fill: parent
    property int barsize: 200
    property alias content: cont
    scale: 1

    Image {
        id: topleftcorner
        source: "qrc:/images/topleftcorner.svg"

        anchors.left: parent.left
        anchors.top: parent.top

        width: barsize
        height: 75
    }

    Rectangle {
        height: topleftcorner.height*0.38801
        anchors.leftMargin: 5
        anchors.left: topleftcorner.right
        anchors.right: parent.right
        color: "#d06468"

        LCARSText {
            text: "Dynamic content control panel"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 10
        }
    }

    Grid {
        id: buttonGrid
        anchors.top: topleftcorner.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        width: topleftcorner.width *194.89/229.969
        columns: 1
        spacing: 5

        LCARSSiteButton {
            width: parent.width
            text: "Clock"
        }

        LCARSSiteButton {
            width: parent.width
            text: "Mail"
        }

        LCARSSiteButton {
            width: parent.width
            text: "Furbase"
        }

        LCARSSiteButton {
            width: parent.width
            text: "Finger"
        }


    }

    Item {
        id: cont
        anchors.left: topleftcorner.right
        anchors.top: topleftcorner.bottom
        anchors.bottom: bottomleftcorner.top
        anchors.right: parent.right

        Rectangle {
            anchors.fill: parent
            color: "#080800"
        }

    }


    Rectangle {
        color: "#9898f5"

        width: topleftcorner.width *194.89/229.969;
        anchors.top: buttonGrid.bottom
        anchors.left: topleftcorner.left
        anchors.bottom: bottomleftcorner.top
        anchors.topMargin: 5
        anchors.bottomMargin: 5
    }

    Image {
        id: bottomleftcorner
        source: "qrc:/images/bottomleftcorner.svg"

        anchors.left: parent.left
        anchors.bottom: parent.bottom

        width: barsize
        height: 57
    }

    Rectangle {
        height: bottomleftcorner.height*0.38801
        anchors.leftMargin: 5
        anchors.left: bottomleftcorner.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: "#9898f5"

        LCARSText {
            text: ""
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 10
        }
    }


  /*  Image {
        source: "bottommenu.svg"
      //  anchors.bottom: parent.bottom
    }*/
}
