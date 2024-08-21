import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: loginPage

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#99f0f0f0"

        Column {
            spacing: 20
            anchors.centerIn: parent

            TextField {
                id: usernameField
                placeholderText: "Username"
                width: 250
                onAccepted: {
                    loginController.login(usernameField.text, passwordField.text)
                }
            }

            TextField {
                id: passwordField
                placeholderText: "Password"
                echoMode: TextInput.Password
                width: 250
                onAccepted: {
                    loginController.login(usernameField.text, passwordField.text)
                }
            }

            Row {
                spacing: 10
                width: 250
                Button {
                    text: "Login"
                    onClicked: {
                        // Handle login logic here
                        loginController.login(usernameField.text, passwordField.text)
                    }
                }

                Button {
                    id: signUpButton
                    text: "Sign Up"
                    onClicked: {
                        // Handle sign-up navigation here
                        navigator.navigateToSignUp()
                    }
                }

            }
            Text {
                text: loginController.notificationText
                anchors.top: signUpButton.bottom
                anchors.horizontalCenter:  parent
            }
        }
    }
}
