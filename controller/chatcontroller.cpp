#include "chatcontroller.h"


void ChatController::setChatPartnerName(QString chatPartnerName)
{
    m_chatPartnerName = chatPartnerName;
}

QString ChatController::getChatPartnerName()
{
    return m_chatPartnerName;
}

QString ChatController::getMyUserName() const
{
    return myUserName;
}

void ChatController::setMyUserName(const QString &value)
{
    myUserName = value;
}

int ChatController::getMyUserId() const
{
    return myUserId;
}

void ChatController::setMyUserId(int value)
{
    myUserId = value;
}

ChatModel *ChatController::getChatModel() const
{
    return mChatModel;
}

void ChatController::setChatModel(ChatModel *chatModel)
{
    mChatModel = chatModel;
}

void ChatController::onTextMessageReceived(QString message)
{
    // Convert the QString to a QByteArray
    QByteArray jsonBytes = message.toUtf8();

    // Parse the JSON string into a QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes);

    // Check if the JSON document is valid and is an object
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // Extract the QJsonObject from the QJsonDocument
        QJsonObject jsonObject = jsonDoc.object();

        // Create a QMap to store the JSON data
        QMap<QString, QVariant> map;

        // Iterate through the QJsonObject and fill the QMap
        for (auto it = jsonObject.begin(); it != jsonObject.end(); ++it) {
            map.insert(it.key(), it.value().toVariant());
        }
        if(jsonObject.contains("senderName")
                && jsonObject.contains("receiverName")
                && jsonObject.contains("senderId")
                && jsonObject.contains("receiverId")
                && jsonObject.contains("message")){
            TextMessage mTextMessage = TextMessage::Builder()
                    .setMessageId(-1) //dont know message id yet, skip this
                    .setMyName(map["senderName"].toString())
                    .setChatPartnerName(map["receiverName"].toString())
                    .setSenderId(map["senderId"].toInt())
                    .setReceiverId(map["receiverId"].toInt())
                    .setMessage(map["message"].toString())
                    .setSentAt("") // dont know yet, skip this
                    .build();

            mChatModel->setAddedData(mTextMessage);
        }

    }
    qDebug(message.toLatin1());
}

ChatController::ChatController(QObject *parent) : QObject(parent)
{
    qDebug("init chat controller");
    connect(mWebsocketClient, &WebsocketClient::textMessageReceivedDelegate, this, &ChatController::onTextMessageReceived);
}

int ChatController::chatPartnerId()
{
    return m_chatPartner;
}

void ChatController::sendMessage(QString message)
{
    mWebsocketClient->sendTextMessage(getMyUserName(), getChatPartnerName(),message, getMyUserId(), chatPartnerId());
    TextMessage mTextMessage = TextMessage::Builder()
            .setMessageId(-1) //dont know message id yet, skip this
            .setMyName(getMyUserName())
            .setChatPartnerName(getChatPartnerName())
            .setSenderId(getMyUserId())
            .setReceiverId(chatPartnerId())
            .setMessage(message)
            .setSentAt("") // dont know yet, skip this
            .build();

    mChatModel->setAddedData(mTextMessage);
    qDebug(message.toLatin1());
}

void ChatController::setChatPartner(int chatPartner)
{
    if (m_chatPartner == chatPartner)
        return;

    m_chatPartner = chatPartner;
    emit chatPartnerChanged(m_chatPartner);
    qDebug("User id who we want to chat with : " + QString::number(m_chatPartner).toLatin1());

}
