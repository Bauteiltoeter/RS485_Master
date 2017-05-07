import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    property string text: ""
    property color normalColor: "#FF9900"
    property color clickedColor: "#BB6600"
    property int defaultWidth: 200
    property bool active: false
    signal clicked;

    color: clickArea.pressed? clickedColor: normalColor
    width: (active) ? defaultWidth+20 : defaultWidth

    height: 50
    LCARSText {

        text: parent.text
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 5
        anchors.bottomMargin: 5

    }

    MouseArea {
        id: clickArea
        anchors.fill: parent

        onClicked: {
            parent.clicked();
        }
    }
}
