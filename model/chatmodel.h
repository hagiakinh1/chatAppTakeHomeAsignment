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
    Q_PROPERTY(TextMessage addedData READ addedData WRITE setAddedData NOTIFY dataAdded)

    TextMessage m_addedData;

public:
    explicit ChatModel();

signals:    
void addedDataChanged(TextMessage addedData);

void dataAdded(TextMessage addedData);

public slots:
    void setCurrentUserName(QString userName);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setAllData(const QList<TextMessage> &data);
    void setAddedData(const TextMessage &singleTextMessage);
    QHash<int, QByteArray> roleNames() const;
    QString getUserName() const;
    TextMessage addedData() const;
};

#endif // CHATMODEL_H
