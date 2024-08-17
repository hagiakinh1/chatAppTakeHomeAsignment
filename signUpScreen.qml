import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    id: signUpPage

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#f0f0f0"

        Column {
            spacing: 20
            anchors.centerIn: parent

            TextField {
                id: usernameField
                placeholderText: "Username"
                width: 250
            }

            TextField {
                id: passwordField
                placeholderText: "Password"
                echoMode: TextInput.Password
                width: 250
            }

            TextField {
                id: repeatPasswordField
                placeholderText: "Repeat Password"
                echoMode: TextInput.Password
                width: 250
            }

            Button {
                text: "Sign Up"
                width: 250
                onClicked: {
                    // Handle sign-up logic here
                    if(passwordField.text ===repeatPasswordField.text){
                        loginController.signUp(usernameField.text, passwordField.text)
                    }else{
                        console.log("repeatPasswordField doesnt match")
                    }

                }
            }
            Button {
                text: "Back"
                width: 250
                onClicked: {
                    // Handle back navigation here
                    navigator.navigateToPreviousPage()
                }
            }
        }
    }
}
