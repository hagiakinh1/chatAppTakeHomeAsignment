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
                //current user is the receiver
                Binding on anchors.left {
                            when: loginController.getUserId() === model.receiverId
                            value: parent.left
                }
                //current user is the sender
                Binding on anchors.right {
                    when: !(loginController.getUserId() === model.receiverId)
                    value: parent.right
                }
                    Column {

                        spacing: 20
                        Text {
                            id: userNameText
                            text: {
                                //
                                if (!(loginController.getUserId() === model.receiverId)){
                                    return model.user
                                }else{
                                    return model.chatPartner
                                }
                            }
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

    TextArea{
        anchors.top: chatHistoryListView.bottom
        anchors.margins: 50
        id: messageInput
        height: 100
        z:1
        width: chatHistoryListView.width

    }
    Rectangle{
        border.width: 1
        color: "#f0f0f0"
        radius: 5
        z:0
        anchors.fill: messageInput
    }

    Button{
        id:sendButton
        anchors.top: messageInput.bottom
        text: "send"
        onClicked: {
            chatController.sendMessage(messageInput.text)
            //reset text
            messageInput.text = ""
        }
    }

}
