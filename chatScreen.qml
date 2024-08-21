import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id:rootId
    anchors.fill: parent
    function onActionToSendMsg(){
        if (messageInput.text !== ""){
            chatController.sendMessage(messageInput.text)
            //reset text
            messageInput.text = ""
        }
    }

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
            property var sender : !(loginController.getUserId() === model.receiverId)
            radius: 5
            border.width: 1
            width: parent.width* 0.8
            anchors.margins: 10
            height: 50
            color: "#99f0f0f0"
            //current user is the receiver
            Binding on anchors.left {
                when: !sender
                value: parent.left
            }
            //current user is the sender
            Binding on anchors.right {
                when: sender
                value: parent.right
            }


            gradient: Gradient{
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.4; color: sender ? "#32CEF2" : "#252B35"; }
                GradientStop { position: 1.0; color: "transparent" }
            }
            Column {

                spacing: 20
                Text {
                    id: userNameText
                    text: {
                        //
                        if (sender){
                            return model.user
                        }else{
                            return model.chatPartner
                        }
                    }
                    color:"#FFFFFF"
                    font.pixelSize: 20
                    width: parent.width * 0.3
                }

                Text {
                    id:messageText
                    anchors.top:userNameText.bottom
                    text: model.message
                    font.pixelSize: 16
                    width: parent.width * 0.6
                    color: "#FFFFFF"
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            id: chatScrollbar
            policy: ScrollBar.AsNeeded
        }
        Component.onCompleted: {
            positionViewAtEnd() // scroll to the end.

        }
        Connections{
            target: chatModel
            onDataAdded: {
                //automatically scroll down the bottom if  user is reading the latest message.
                console.log("on data added" )
                if((chatScrollbar.position + chatScrollbar.size) > 0.99){
                    console.log("scroll to the end ")
                    chatHistoryListView.positionViewAtEnd() // scroll to the end.
                }
            }
        }
    }

    TextArea{
        anchors.top: chatHistoryListView.bottom
        anchors.topMargin: 50
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        id: messageInput
        height: 60
        z:1
        width: chatHistoryListView.width
        Keys.onReleased: {
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                // Prevent the Enter key from adding a newline
                event.accepted = true

                onActionToSendMsg()
            }
        }
    }
    Rectangle{
        border.width: 1
        color: "#f0f0f0"
        radius: 5
        z:0
        anchors.fill: messageInput
    }

    Rectangle{
        id:sendButton
        anchors.top: messageInput.bottom
        anchors.left: messageInput.left
        anchors.topMargin: 10
        width: 50
        height: 30
        radius: 5
        border.width: 1
        color:"transparent"
        Text{
            anchors.centerIn: parent
            anchors.fill: parent
            text: "Send now"
            color: "white"
        }
        MouseArea{
            anchors.centerIn: parent
            anchors.fill: parent
            onClicked: {
                onActionToSendMsg()
            }
        }
    }



}
