#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>

class ChatController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int chatPartner READ chatPartner WRITE setChatPartner NOTIFY chatPartnerChanged)
    int m_chatPartner;

public:
    explicit ChatController(QObject *parent = nullptr);

    int chatPartner() ;

signals:


    void chatPartnerChanged(int chatPartner);

public slots:
    void setChatPartner(int chatPartner);

};

#endif // CHATCONTROLLER_H
