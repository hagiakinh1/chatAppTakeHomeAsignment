#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include<model/chatmodel.h>
#include<websocketclient.h>
#include<model/chatmodel.h>

class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int chatPartnerId READ chatPartnerId WRITE setChatPartner NOTIFY chatPartnerChanged)
    int m_chatPartner;
    QString m_chatPartnerName;
    int myUserId;
    QString myUserName;
    ChatModel * mChatModel;
    WebsocketClient* mWebsocketClient = &WebsocketClient::getInstance();
public:
    explicit ChatController(QObject *parent = nullptr);

    int chatPartnerId() ;
    Q_INVOKABLE void sendMessage(QString message);
    Q_INVOKABLE void setChatPartnerName(QString chatPartnerName);
    QString getChatPartnerName();

    QString getMyUserName() const;
    void setMyUserName(const QString &value);

    int getMyUserId() const;
    void setMyUserId(int value);

    ChatModel *getChatModel() const;
    void setChatModel(ChatModel *chatModel);

signals:
    
    
    void chatPartnerChanged(int chatPartnerId);
    
public slots:
    void setChatPartner(int chatPartnerId);
    void onTextMessageReceived(QString message);


};

#endif // CHATCONTROLLER_H
