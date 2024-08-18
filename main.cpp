#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <model/dataaccessobject.h>
#include <QTextStream>
#include <controller/navigator.h>
#include <QQmlContext>
#include <controller/logincontroller.h>
#include <model/contactmodel.h>
#include <QThread>
#include <controller/chatcontroller.h>



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ChatController mChatController;
    LoginController mLoginController;
    ContactModel mContactModel;
    QObject::connect(&mLoginController, LoginController::userChanged, &mContactModel, ContactModel::setDataFromUserId);


    engine.rootContext()->setContextProperty("navigator", &Navigator::getInstance());
    engine.rootContext()->setContextProperty("loginController", &mLoginController);
    engine.rootContext()->setContextProperty("contactModel", &mContactModel);
    engine.rootContext()->setContextProperty("chatController", &mChatController);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    NavigatorDispatcher::start();



    return app.exec();
}
