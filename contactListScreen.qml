import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
        anchors.fill: parent
    Button{
        anchors.left: parent.left
        id: signOffbutton
        text: "sign off"
        onClicked: navigator.navigateToPreviousPage()
    }
    ListView {
        anchors.top: signOffbutton.bottom
        anchors.horizontalCenter: parent
            id: contactListView
            width: parent.width
            height: parent.height
            model: contactModel

            delegate: Item {
                width: parent.width
                height: 100
                Column {

                    spacing: 50
                    anchors.verticalCenter: parent.verticalCenter

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
