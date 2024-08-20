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
#include<model/textmessage.h>
#include <list>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ChatController mChatController;
    LoginController mLoginController;
    ContactModel mContactModel;
    ChatModel mChatModel;
    mChatController.setChatModel(&mChatModel);

    QObject::connect(&mChatController, &ChatController::chatPartnerChanged, [&mLoginController, &mChatController, &mChatModel]() {
        LoginController* loginPtr = &mLoginController;
        ChatController* chatPtr = &mChatController;

        QList<QVariantList> messages = DataAccessObject::getInstance().readMessagesBetweenUsers(loginPtr->getUserId(), chatPtr->chatPartnerId());
        QList<TextMessage> mTextMessages;
        for (const QVariantList& message : messages) {

            TextMessage mTextMessage = TextMessage::Builder()
                    .setMessageId(message[0].toInt())
                    .setMyName(mLoginController.getUserName())
                    .setChatPartnerName(mChatController.getChatPartnerName())
                    .setSenderId(message[1].toInt())
                    .setReceiverId(message[2].toInt())
                    .setMessage(message[3].toString())
                    .setSentAt(message[4].toString())
                    .build();
            mTextMessages<< mTextMessage;

        }
        mChatModel.setCurrentUserName(mLoginController.getUserName());
        mChatModel.setAllData(mTextMessages);
        mChatController.setMyUserId(mLoginController.getUserId());
        mChatController.setMyUserName(mLoginController.getUserName());

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
