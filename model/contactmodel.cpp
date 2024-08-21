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
    if (role == ContactListModelRole::UserName){
        return m_data[index.row()][1]; // 0 user_id, 1 username, 2 latest message, 3 send at
    }else if (role == ContactListModelRole::LatestMessage){
        return m_data[index.row()][2];
    }else if (role == ContactListModelRole::UserId){
        return m_data[index.row()][0];
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
    connect(&contactListDataLoadedWatcher, &QFutureWatcher<void>::finished, this, [this](){
        //update the ui
        beginInsertRows(QModelIndex(), 0, m_data.count());
        endInsertRows();
    });
    QFuture<void> future = QtConcurrent::run([this, user_id]()
    {
        //Implement a loading screen in the future
        setData( DataAccessObject::getInstance().readAllUsersWithLatestMessage(user_id));
    });
    contactListDataLoadedWatcher.setFuture(future);
}

QHash<int, QByteArray> ContactModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ContactListModelRole::UserName] = "userName";
    roles[ContactListModelRole::LatestMessage] = "latestMessage";
    roles[ContactListModelRole::UserId] = "userId";
    return roles;
}


