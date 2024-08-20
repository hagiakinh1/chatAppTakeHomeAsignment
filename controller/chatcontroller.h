#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include<model/chatmodel.h>
#include<websocketclient.h>

class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int chatPartner READ chatPartner WRITE setChatPartner NOTIFY chatPartnerChanged)
    int m_chatPartner;
    QString m_chatPartnerName;
    int myUserId;
    QString myUserName;

    WebsocketClient* mWebsocketClient = &WebsocketClient::getInstance();

public:
    explicit ChatController(QObject *parent = nullptr);

    int chatPartner() ;
    Q_INVOKABLE void sendMessage(QString message);
    Q_INVOKABLE void setChatPartnerName(QString chatPartnerName);
    QString getChatPartnerName();

    QString getMyUserName() const;
    void setMyUserName(const QString &value);

    int getMyUserId() const;
    void setMyUserId(int value);

signals:
    
    
    void chatPartnerChanged(int chatPartner);
    
public slots:
    void setChatPartner(int chatPartner);

};

#endif // CHATCONTROLLER_H
