#include "chatcontroller.h"



ChatModel *ChatController::chatModel() const
{
    return mChatModel;
}

void ChatController::setChatModel(ChatModel *chatModel)
{
    mChatModel = chatModel;
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
    if(mChatModel!=nullptr)
    qDebug(mChatModel->getUserName().toLatin1()+ "sent"+ message.toLatin1());
}

void ChatController::setChatPartner(int chatPartner)
{
    if (m_chatPartner == chatPartner)
        return;

    m_chatPartner = chatPartner;
    emit chatPartnerChanged(m_chatPartner);
    qDebug("User id who we want to chat with : " + QString::number(m_chatPartner).toLatin1());

}
