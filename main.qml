import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Loader{
        id:loader
        anchors.centerIn: parent
    }
    Connections {
            target: navigator
            onScreenChanged: {
                loader.setSource(Qt.resolvedUrl(screen))
                console.log("navigate to " + screen)
            }
    }



}
