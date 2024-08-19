#include "chatmodel.h"


ChatModel::ChatModel()
{

}

void ChatModel::setCurrentUserName(QString userName)
{
    this->userName = userName;
}

int ChatModel::rowCount(const QModelIndex &parent) const
{
    return chatHistoryData.count();
}

QVariant ChatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= chatHistoryData.count())
            return QVariant();

        const TextMessage &textMessage = chatHistoryData[index.row()];

        switch (role) {
            case ChatModelRole::MessageIdRole:
                return textMessage.getMessageId();
            case ChatModelRole::UserRole:
                return this->userName;
            case ChatModelRole::ChatPartnerRole:
                return textMessage.getChatPartnerName();
            case ChatModelRole::MessageRole:
                return textMessage.getMessage();
            case ChatModelRole::SenderIdRole:
                return textMessage.getSenderId();
            case ChatModelRole::ReceiverIdRole:
                return textMessage.getReceiverId();
            case ChatModelRole::SentAtRole:
                return textMessage.getSentAt();
            default:
                return QVariant();
        }
}

bool ChatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

void ChatModel::setAllData(const QList<TextMessage> &data)
{
    this->chatHistoryData = data;
}

QHash<int, QByteArray> ChatModel::roleNames() const
{

        QHash<int, QByteArray> roles;
        roles[ChatModelRole::MessageIdRole] = "messageId";
        roles[ChatModelRole::UserRole] = "user";
        roles[ChatModelRole::ChatPartnerRole] = "chatPartner";
        roles[ChatModelRole::MessageRole] = "message";
        roles[ChatModelRole::SenderIdRole] = "senderId";
        roles[ChatModelRole::ReceiverIdRole] = "receiverId";
        roles[ChatModelRole::SentAtRole] = "sentAt";
        return roles;

}

QString ChatModel::getUserName() const
{
    return this->userName;
}
