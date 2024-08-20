#ifndef CHATMODEL_H
#define CHATMODEL_H

#include <QAbstractListModel>
#include <QVariantList>
#include<QList>
#include <QObject>
#include"textmessage.h"
enum ChatModelRole {
    MessageIdRole = Qt::UserRole + 1,
    UserRole,
    ChatPartnerRole,
    MessageRole,
    SenderIdRole,
    ReceiverIdRole,
    SentAtRole
};
class ChatModel :  public QAbstractListModel
{
    Q_OBJECT
    QList<TextMessage> chatHistoryData;
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
    void setAllData(const QList<TextMessage> &data);
    void addData(const TextMessage &singleTextMessage);
    QHash<int, QByteArray> roleNames() const;
    QString getUserName() const;

};

#endif // CHATMODEL_H
