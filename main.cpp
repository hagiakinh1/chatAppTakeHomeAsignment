#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<model/dataaccessobject.h>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    DataAccessObject &a  = DataAccessObject::getInstance();
    a.createUser("kinh", "abc");
    a.createUser("kinh1", "abc1");
    a.createUser("kinh2", "abc2");


    QList<QVariantList> users = a.readAllUsers();
    for (const QVariantList& user : users) {
        auto userInfo = "User ID: " + QString::number(user[0].toInt())+
                + " Username: " + user[1].toString()
                + " Password Hash: " + user[2].toString()
                + " Created At: " + user[3].toString();
            QTextStream(stdout)<< userInfo<< "\n";
    }

    a.createMessage(1,2, "ei, wtf");
    a.createMessage(2,1, "what?");
    a.createMessage(1,2, "nothing, nevermind");
    QList<QVariantList> messages = a.readMessagesBetweenUsers(1,2);
        for (const QVariantList& message : messages) {
            auto messagesInfo = "Message ID: " + QString::number(message[0].toInt())
                + " Sender ID: " + QString::number(message[1].toInt())
                + " Receiver ID: " + QString::number(message[2].toInt())
                + " Message Text: " + message[3].toString()
                + " Sent At: " + message[4].toString();
            QTextStream(stdout)<< messagesInfo << "\n";

        }


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
