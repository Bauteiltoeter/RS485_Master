import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Rectangle {
    property string text: ""

    signal clicked;

    color: "#FF9900"
    width: 200
    height: 50
    LCARSText {

        text: parent.text
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 5
        anchors.bottomMargin: 5

    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.clicked();
        }
    }
}
