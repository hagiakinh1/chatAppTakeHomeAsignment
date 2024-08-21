import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    //example of valid password: aA0&llll
    function validatePassword(pw) {

        return /[A-Z]/       .test(pw) &&
               /[a-z]/       .test(pw) &&
               /[0-9]/       .test(pw) &&
               /[^A-Za-z0-9]/.test(pw) &&
               pw.length > 6;

    }
    function validateUsername(username) {

        return username.length > 6;

    }
    id: signUpPage

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
                id: signUpButton
                text: "Sign Up"
                width: 250
                onClicked: {
                    // Handle sign-up logic here
                    if(passwordField.text ===repeatPasswordField.text){

                        if(validateUsername(usernameField.text) && validatePassword(passwordField.text)){
                            loginController.signUp(usernameField.text, passwordField.text)
                        }else{
                            notificationText.text = "User name or password invalid"
                        }
                    }else{
                        console.log("repeatPasswordField doesnt match")
                        notificationText.text = "Repeat password field doesnt match"
                    }

                }
            }
            Text {
                id:notificationText
                text: ""
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
