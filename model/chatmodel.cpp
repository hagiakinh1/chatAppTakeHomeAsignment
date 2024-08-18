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
    if (role == ChatModelRole::User){
        return this->userName; // [message ID:  sender id: , receiver id: , message]
    }else if (role == ChatModelRole::ChatPartner){
        return "No partner name yet, fix this later";
    }else if (role == ChatModelRole::Message){
        return chatHistoryData[index.row()][3];
    }else if (role == ChatModelRole::SenderId){
        return chatHistoryData[index.row()][1];
    }else if (role == ChatModelRole::ReceiverId){
        return chatHistoryData[index.row()][2];
    }
}

bool ChatModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}

void ChatModel::setAllData(const QList<QVariantList> &data)
{
    this->chatHistoryData = data;
}

QHash<int, QByteArray> ChatModel::roleNames() const
{

        QHash<int, QByteArray> roles;
        roles[ChatModelRole::User] = "user";
        roles[ChatModelRole::ChatPartner] = "chatPartner";
        roles[ChatModelRole::Message] = "message";
        roles[ChatModelRole::SenderId] = "senderId";
        roles[ChatModelRole::ReceiverId] = "receiverId";
        return roles;

}
