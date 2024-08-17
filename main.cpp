#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <model/dataaccessobject.h>
#include <QTextStream>
#include <controller/navigator.h>
#include <QQmlContext>
#include <controller/logincontroller.h>
#include <model/contactmodel.h>
#include <QThread>



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    DataAccessObject &a  = DataAccessObject::getInstance();

//    a.createMessage(1,2, "aaaaaa");
//    a.createMessage(1,3, "aa");
//    a.createMessage(3,1, "aab");
//    a.createMessage(4,1, "hey");

    a.readAllUsersWithLatestMessage(1);
    QList<QVariantList> users = a.readAllUsers();
        for (const QVariantList& user : users) {
            auto userInfo = "User ID: " + QString::number(user[0].toInt())+
                    + " Username: " + user[1].toString()
                    + " Password Hash: " + user[2].toString()
                    + " Created At: " + user[3].toString();
                QTextStream(stdout)<< userInfo<< "\n";
        }
        if(a.checkUserExists("kinh", "abc")) {
            qDebug("yes");
        }
        else{
            qDebug("no");
        }

    LoginController mLoginController;
    ContactModel mContactModel;
     QObject::connect(&mLoginController, LoginController::userChanged, &mContactModel, ContactModel::setDataFromUserId);


    engine.rootContext()->setContextProperty("navigator", &Navigator::getInstance());
    engine.rootContext()->setContextProperty("loginController", &mLoginController);
    engine.rootContext()->setContextProperty("contactModel", &mContactModel);

//    NavigatorDispatcher::dispatch(UserOpenContactList());
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    NavigatorDispatcher::start();



    return app.exec();
}
