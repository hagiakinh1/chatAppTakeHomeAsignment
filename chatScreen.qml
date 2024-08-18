import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id:rootId
    anchors.fill: parent
    Button{
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.topMargin: 10

        id: backButton
        text: "back"
        onClicked: navigator.navigateToPreviousPage()
    }
    ListView {
        anchors.top: backButton.bottom
        anchors.topMargin: 50
        id: chatHistoryListView
        width: parent.width
        height: 200
        model: chatModel

        delegate:
            Rectangle {
                radius: 5
                border.width: 1
                width: parent.width* 0.8
                height: 50
                color: "#f0f0f0"
                Binding on anchors.left {
                            when: loginController.getUserId() === model.receiverId
                            value: parent.left
                        }

                Binding on anchors.right {
                    when: !(loginController.getUserId() === model.receiverId)
                    value: parent.right
                }
                    Column {

                        spacing: 20
                        Text {
                            id: userNameText
                            text: model.senderId
                            font.pixelSize: 20
                            width: parent.width * 0.3
                        }

                        Text {
                            id:messageText
                            anchors.top:userNameText.bottom
                            text: model.message
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
