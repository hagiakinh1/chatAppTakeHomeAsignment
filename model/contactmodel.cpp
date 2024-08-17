#include "contactmodel.h"

ContactModel::ContactModel()
{

}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.count())
                return QVariant();
    if (role == ModelRole::UserName){
        return m_data[index.row()][1];
    }else if (role == ModelRole::LatestMessage){
        return m_data[index.row()][2];
    }

}

bool ContactModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //To do
}

ContactModel::setData(const QList<QVariantList> &data)
{
    m_data = data;
}

ContactModel::setDataFromUserId(int user_id)
{
    setData( DataAccessObject::getInstance().readAllUsersWithLatestMessage(user_id));
}

QHash<int, QByteArray> ContactModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ModelRole::UserName] = "userName";
    roles[ModelRole::LatestMessage] = "latestMessage";

    return roles;
}


