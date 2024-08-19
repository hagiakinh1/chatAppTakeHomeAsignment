#ifndef TEXTMESSAGE_H
#define TEXTMESSAGE_H

#include<QString>

class TextMessage
{
    int messageId;
    QString myName;
    QString chatPartnerName;
    int senderId;
    int receiverId;
    QString message;
    QString sentAt;
public:

    // Default constructor
        TextMessage();

        // Parameterized constructor
        TextMessage(int messageId, const QString &myName, const QString &chatPartnerName,
                    int senderId, int receiverId, const QString &message, const QString &sentAt);

        // Copy constructor
        TextMessage(const TextMessage &other);

        // Move constructor
        TextMessage(TextMessage &&other) noexcept;

        // Copy assignment operator
        TextMessage& operator=(const TextMessage &other);

        // Move assignment operator
        TextMessage& operator=(TextMessage &&other) noexcept;

        // Destructor
        ~TextMessage();

        // Method to return a string representation of the message
        QString toString() const;
        int getMessageId() const;
        void setMessageId(int value);
        QString getMyName() const;
        void setMyName(const QString &value);
        QString getChatPartnerName() const;
        void setChatPartnerName(const QString &value);
        int getSenderId() const;
        void setSenderId(int value);
        int getReceiverId() const;
        void setReceiverId(int value);
        QString getMessage() const;
        void setMessage(const QString &value);
        QString getSentAt() const;
        void setSentAt(const QString &value);


        // Builder class
        class Builder
        {
        private:
            int messageId;
            QString myName;
            QString chatPartnerName;
            int senderId;
            int receiverId;
            QString message;
            QString sentAt;

        public:
            Builder& setMessageId(int id);
            Builder& setMyName(const QString &name);
            Builder& setChatPartnerName(const QString &name);
            Builder& setSenderId(int id);
            Builder& setReceiverId(int id);
            Builder& setMessage(const QString &msg);
            Builder& setSentAt(const QString &sentAt);
            TextMessage build() const;
        };
};

#endif // TEXTMESSAGE_H
