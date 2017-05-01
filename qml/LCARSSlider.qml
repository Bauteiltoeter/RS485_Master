import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Slider {
    id: slider

    style: SliderStyle {

        groove: Item {


            height: 60

            /*Rectangle {
                color: "#FF0000"
                anchors.fill: parent
            }*/


            Grid {
                x: 15
                y: 8
                spacing: (slider.width-30-9*2)/10
                rows: 1

                Repeater {

                    model: 11
                    Item {
                        width: 1
                        height: 1
                        LCARSText {
                            font.pixelSize: 25
                            anchors.centerIn: parent
                            text: index*10+"%"


                            color: index%2==0? "#cc6666" : "#ffcc99"
                        }
                    }
                }
            }


            Grid {
                x: 15
                y: 30-10
                spacing: 2
                rows: 1

                Repeater {
                    model: 10
                    Rectangle {

                        height: 10

                        width: (slider.width-30-9*2)/10
                        color: index%2==0? "#cc6666" : "#ffcc99"
                    }
                }
            }
        }


        handle: Item {
            width: 30
            height: 60
            Image {
                source: "qrc:/images/triangle.svg"
                anchors.bottom: parent.bottom
                width: 30
                height:30
            }
        }

    }
}
