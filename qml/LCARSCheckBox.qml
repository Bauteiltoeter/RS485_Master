import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

CheckBox {
    id: cb
    text: "-"
    checked: false

    style: CheckBoxStyle {
        label: LCARSText {
            text: cb.text
            font.pixelSize: 35
            color: control.checked ? "#ff3232" : "#9999ff"
        }

        indicator: Rectangle{
            implicitWidth: 35
            implicitHeight: 35
            radius: 3
            border.color: control.checked ? "#ff3232" : "#9999ff"
            border.width: 5
            color: "#000000"

            Image {
                source: "qrc:/images/triangle.svg"
                visible: control.checked
                anchors.centerIn: parent
                width: 20
                height:20
                rotation: 90
            }
        }
    }
 }
