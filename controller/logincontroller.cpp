#include "logincontroller.h"

LoginController::LoginController(QObject *parent) : QObject(parent)
{

}

void LoginController::verifyLogin()
{
    //check for null
    if ((this->userName != NULL) && !(this->password != NULL)) {
        qDebug("user name or password incorrect");
        setNotificationText("user name or password incorrect");
        return;
    }

    DataAccessObject &mDataAccessObject  = DataAccessObject::getInstance();
    setUserId(mDataAccessObject.findUser(this->userName, this->password));

    if(user_id >=1){
        NavigatorDispatcher::dispatch(UserOpenContactList());
        setNotificationText("");

    }else{
        qDebug("user name or password incorrect");
        setNotificationText("user name or password incorrect");
    }
}

int LoginController::getUserId()
{
    return user_id;
}

LoginController::login(QString userName, QString password)
{
    this->userName = userName;
    this->password = password;
    qDebug(userName.toLatin1() + " " + password.toLatin1());
    verifyLogin();
}

LoginController::signUp(QString userName, QString password)
{
    qDebug(userName.toLatin1() + " " + password.toLatin1());

    DataAccessObject &mDataAccessObject  = DataAccessObject::getInstance();
    setUserId( mDataAccessObject.findUser(this->userName, this->password));
    if(!(user_id >=1) // user_id >=1 means user exists
            && (userName.length() >=3)
            && (password) >=3){
        if(mDataAccessObject.createUser(userName, password)){
            qDebug("create user " + userName.toLatin1() + " " + password.toLatin1());
            setNotificationText("");
            NavigatorDispatcher::dispatch(UserOpenContactList());

        }


    }else{
        qDebug("user name already exists");
        setNotificationText("user name already exists");
    }
}
void LoginController::setUserId(int user_id){
    user_id = user_id;
    emit userChanged(user_id);
}
