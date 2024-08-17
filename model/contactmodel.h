#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H
#include <QAbstractListModel>
#include <QVariantList>
#include <QObject>
#include"dataaccessobject.h"
enum ModelRole {
    UserName = Qt::UserRole + 1,
    LatestMessage
};
class ContactModel : public QAbstractListModel
{
    Q_OBJECT
public:
    ContactModel();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    setData(const QList<QVariantList> &data) ;
    QHash<int, QByteArray> roleNames() const;
public slots:
    setDataFromUserId(int user_id) ;

private:
    QList<QVariantList> m_data;
};

#endif // CONTACTMODEL_H
