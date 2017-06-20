import QtQuick 2.0
import Displaymaster.contentManager 1.0

LCARSButtonPanel {
    id: dynamicConentPanel
    objectName: "dynamicConentPanel"
    barsize: 200
    anchors.fill: parent

    Component.onCompleted: {
        ContentManager.load()
    }


    header: ContentManager.headerText
    footer: ContentManager.footerText
    buttons: ContentManager.buttons
    contents: ContentManager.mainWindows

    onVisibleChanged: {
        ContentManager.load();

        ContentManager.visibleChanged(visible);
    }

}
