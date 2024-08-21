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
                    if(validateUsername(usernameField.text) && validatePassword(passwordField.text)){
                        loginController.login(usernameField.text, passwordField.text)
                    }else{
                        notificationText.text = "User name or password is invalid."
                    }                }
            }

            TextField {
                id: passwordField
                placeholderText: "Password"
                echoMode: TextInput.Password
                width: 250
                onAccepted: {
                    if(validateUsername(usernameField.text) && validatePassword(passwordField.text)){
                        loginController.login(usernameField.text, passwordField.text)
                    }else{
                        notificationText.text = "User name or password is invalid."
                    }                }
            }

            Row {
                spacing: 10
                width: 250
                Button {
                    text: "Login"
                    onClicked: {
                        if(validateUsername(usernameField.text) && validatePassword(passwordField.text)){
                            loginController.login(usernameField.text, passwordField.text)
                        }else{
                            notificationText.text = "User name or password is invalid."
                        }
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
                id:notificationText
                text: loginController.notificationText
                anchors.top: signUpButton.bottom
                anchors.horizontalCenter:  parent
            }
        }
    }
}
