#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
class Message
{
    QString myName;
    QString chatPartnerName;
    int senderId;
    int receiverId;
    QString message;
    QString sentAt;

public:
//    Message(const QString &myName, const QString &chatPartnerName, int senderId, int receiverId, const QString &message, const QString &sentAt);
    Message();
    //    QString toString() const;
};

#endif // MESSAGE_H
