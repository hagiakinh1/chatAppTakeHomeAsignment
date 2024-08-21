import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Image{
            id: background
            anchors.fill: parent
            source: "/assets/background.png"
            asynchronous: true
            fillMode: Image.Stretch

            layer.enabled: true
            layer.effect: OpacityMask{
                maskSource: Item{
                    width: background.width
                    height: background.height
                    Rectangle{
                        anchors.centerIn: parent
                        width: background.width
                        height: background.height
                        radius: mainWindow.radius
                    }
                }
            }
        }
    Loader{
        id:loader
        anchors.centerIn: parent
        anchors.fill: parent
    }
    Connections {
            target: navigator
            onScreenChanged: {
                loader.setSource(Qt.resolvedUrl(screen))
                console.log("navigate to " + screen)
            }
    }



}
