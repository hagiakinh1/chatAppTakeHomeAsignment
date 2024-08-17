import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id:rootId
    anchors.fill: parent
    Button{
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.topMargin: 10

        id: signOffbutton
        text: "sign off"
        onClicked: navigator.navigateToPreviousPage()
    }
    ListView {
        anchors.top: signOffbutton.bottom
        anchors.topMargin: 50
            id: contactListView
            width: parent.width
            height: parent.height
            model: contactModel

            delegate: Rectangle {
                radius: 5
                border.width: 1
                width: parent.width
                height: 50
                color: "#f0f0f0"
                Column {

                    spacing: 20
                    Text {
                        id: userNameText
                        text: model.userName
                        font.pixelSize: 20
                        width: parent.width * 0.3
                    }

                    Text {
                        id:latestMessageText
                        anchors.top:userNameText.bottom
                        text: model.latestMessage
                        font.pixelSize: 16
                        width: parent.width * 0.6
                        color: "gray"
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AsNeeded
            }
        }

}
