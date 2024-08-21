import QtQuick 2.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

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

        delegate:
            Rectangle {
            radius: 5
            border.width: 1
            width: parent.width
            height: 50


            gradient: Gradient{
                GradientStop { position: 0.0; color: "transparent" }
                GradientStop { position: 0.4; color: "#3e4f6b"; }
                GradientStop { position: 1.0; color: "transparent" }
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                    //navigate to chat screen and set the userId of the user who we want to chat with
                    //we have to setChatPartnerName first because we have a signal listen to setChatPartner.
                    chatController.setChatPartnerName(model.userName)
                    chatController.setChatPartner(model.userId)
                    navigator.navigateToChat()
                }
            }
            Column {


                spacing: 20
                Text {
                    id: userNameText
                    text: model.userName
                    font.pixelSize: 20
                    width: parent.width * 0.3
                    color: "#FFFFFF"
                }

                Text {
                    id:latestMessageText
                    anchors.top:userNameText.bottom
                    text: model.latestMessage
                    font.pixelSize: 16
                    width: parent.width * 0.6
                    color : "#FFFFFF"
                }
            }
        }

        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }
    }


}
