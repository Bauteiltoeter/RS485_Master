import QtQuick 2.0


Panel {
    anchors.fill: parent
    isBlue: true

    LCARSSlider {
        id: s1
        width: 500
        anchors.centerIn: parent
        inactive: autoCheckbox.checked

        minimumValue: 0
        maximumValue: 100
        updateValueWhileDragging : false


        onValueChanged: {
            con.setBrightness(value);
        }

    }

    LCARSCheckBox {
        id: autoCheckbox
        anchors.top: s1.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Automatic"
    }




}
