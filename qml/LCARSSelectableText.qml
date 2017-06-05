import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

RadioButton {
    property string color: "#00FFFF"

    id: radio
    //property alias text: tf.text

   // property string color: "#ff3232"
    width: 200
    height: 30



    style: RadioButtonStyle {
        label: LCARSText{
            color: radio.color
            text: radio.text

        }

        indicator: Image {
            source: "qrc:/images/triangle.svg"
            width: 15
            height:15
            rotation: 90

            visible: control.checked
        }


    }
}
