#include "chatcontroller.h"


void ChatController::setChatPartnerName(QString chatPartnerName)
{
    m_chatPartnerName = chatPartnerName;
}

QString ChatController::getChatPartnerName()
{
    return m_chatPartnerName;
}

ChatController::ChatController(QObject *parent) : QObject(parent), mWebsocketClient(QUrl(QStringLiteral("ws://localhost:1234")), true)
{
    qDebug("init chat controller");
}

int ChatController::chatPartner()
{
    return m_chatPartner;
}

void ChatController::sendMessage(QString message)
{
    mWebsocketClient.sendTextMessage(message);
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
