import QtQuick 2.0
import QtCharts 2.0


Panel {
    anchors.fill: parent
    isBlue: true

    LCARSButton {
        invert: false
        text: "L1"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -65
        anchors.right: chart.left
    }

    LCARSButton {
        invert: true
        text: "L2"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: chart.left
    }

    LCARSButton {
        invert: true
        text: "L3"
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 65
        anchors.right: chart.left
    }


    ChartView {
        id: chart
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -50
        width: 1000
        height: 700
        theme: ChartView.ChartThemeDark
        antialiasing: true

        LineSeries {
               name: "Voltage"

               XYPoint { x: 0; y: 0 }
               XYPoint { x: 2; y: 191 }
               XYPoint { x: 4; y: 309 }
               XYPoint { x: 6; y: 309 }
               XYPoint { x: 8; y: 191 }
               XYPoint { x: 10; y: 0 }
               XYPoint { x: 12; y: -191}
               XYPoint { x: 14; y: -309 }
               XYPoint { x: 16; y: -309 }
               XYPoint { x: 18; y: -191 }
               XYPoint { x: 20; y: -0}
        }

        LineSeries {
               name: "Current"

               XYPoint { x: 0; y: 0 }
               XYPoint { x: 1; y: 191 }
               XYPoint { x: 3; y: 309 }
               XYPoint { x: 5; y: 309 }
               XYPoint { x: 7; y: 191 }
               XYPoint { x: 9; y: 0 }
               XYPoint { x: 11; y: -191}
               XYPoint { x: 13; y: -309 }
               XYPoint { x: 15; y: -309 }
               XYPoint { x: 17; y: -191 }
               XYPoint { x: 19; y: -0}
        }
    }

    LCARSButton {
        id: voltageButton
        invert: true
        text: "Voltage"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -105
        anchors.top: chart.bottom
        anchors.topMargin: 10
    }

    LCARSButton {
        invert: false
        text: "Power"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 105
        anchors.top: chart.bottom
        anchors.topMargin: 10
    }


}
