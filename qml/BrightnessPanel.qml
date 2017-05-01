import QtQuick 2.0

Panel {
    anchors.fill: parent
    isBlue: true

    LCARSSlider {
        id: s1
        width: 500
        anchors.centerIn: parent

        minimumValue: 0
        maximumValue: 100

        onPressedChanged: {
            con.setBrightness(value);
        }

    }


}
