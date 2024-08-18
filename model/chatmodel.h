#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QVariantList>
#include<QList>
#include <QObject>
enum ChatModelRole {
    User = Qt::UserRole + 1,
    ChatPartner,
    SenderId,
    ReceiverId,
    Message
};
class ChatModel :  public QAbstractListModel
{
    Q_OBJECT
    QList<QVariantList> chatHistoryData;
    QString userName;

public:
    explicit ChatModel();

signals:

public slots:
    void setCurrentUserName(QString userName);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setAllData(const QList<QVariantList> &data);
    QHash<int, QByteArray> roleNames() const;
};

#endif // CHATMODEL_H
