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

ChatController::ChatController(QObject *parent) : QObject(parent)
{
    qDebug("init chat controller");
}

int ChatController::chatPartner()
{
    return m_chatPartner;
}

void ChatController::sendMessage(QString message)
{
    mWebsocketClient->sendTextMessage(getMyUserName(), getChatPartnerName(),message, getMyUserId(), chatPartner());
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
