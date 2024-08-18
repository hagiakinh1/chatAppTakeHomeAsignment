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
#include<model/chatmodel.h>



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ChatController mChatController;
    LoginController mLoginController;
    ContactModel mContactModel;
    ChatModel mChatModel;

    QObject::connect(&mChatController, &ChatController::chatPartnerChanged, [&mLoginController, &mChatController, &mChatModel]() {
        LoginController* loginPtr = &mLoginController;
        ChatController* chatPtr = &mChatController;

        QList<QVariantList> messages = DataAccessObject::getInstance().readMessagesBetweenUsers(loginPtr->getUserId(), chatPtr->chatPartner());

        for (const QVariantList& message : messages) {
            QString messageInfo = "message ID: " + QString::number(message[0].toInt())
                + " sender id: " + QString::number(message[1].toInt())
                + " receiver id: " + QString::number(message[2].toInt())
                + " message: " + message[3].toString()
                + " sent at " + message[4].toString();
            QTextStream(stdout) << messageInfo << "\n";
        }
        mChatModel.setAllData(messages);
        mChatModel.setCurrentUserName(mLoginController.getUserName());
    });
    QObject::connect(&mLoginController, LoginController::userChanged, &mContactModel, ContactModel::setDataFromUserId);




    engine.rootContext()->setContextProperty("navigator", &Navigator::getInstance());
    engine.rootContext()->setContextProperty("loginController", &mLoginController);
    engine.rootContext()->setContextProperty("contactModel", &mContactModel);
    engine.rootContext()->setContextProperty("chatController", &mChatController);
    engine.rootContext()->setContextProperty("chatModel", &mChatModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    NavigatorDispatcher::start();



    return app.exec();
}
