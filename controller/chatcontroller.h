#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include<model/chatmodel.h>

class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int chatPartner READ chatPartner WRITE setChatPartner NOTIFY chatPartnerChanged)
    int m_chatPartner;
    ChatModel* mChatModel;

public:
    explicit ChatController(QObject *parent = nullptr);

    int chatPartner() ;
    Q_INVOKABLE void sendMessage(QString message);
    ChatModel *chatModel() const;
    void setChatModel(ChatModel *chatModel);

signals:
    
    
    void chatPartnerChanged(int chatPartner);
    
public slots:
    void setChatPartner(int chatPartner);

};

#endif // CHATCONTROLLER_H
