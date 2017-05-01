import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Panel {
    property alias text: tf.text

    id: panel

    TextArea {
        id: tf
        font.family: "LCARSGTJ3"
        font.pixelSize: 40
        anchors.fill: parent
        anchors.topMargin: panel.calcHeight()*0.3
        anchors.bottomMargin: panel.calcHeight()*0.3
        anchors.leftMargin: panel.calcWidth()
        anchors.rightMargin: panel.calcWidth()
        style: TextAreaStyle {

            textColor: "#FF9900"
            backgroundColor: "#000"
        }
    }
}
