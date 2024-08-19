#include "TextMessage.h"

// Default constructor
int TextMessage::getMessageId() const
{
    return messageId;
}

void TextMessage::setMessageId(int value)
{
    messageId = value;
}

QString TextMessage::getMyName() const
{
    return myName;
}

void TextMessage::setMyName(const QString &value)
{
    myName = value;
}

QString TextMessage::getChatPartnerName() const
{
    return chatPartnerName;
}

void TextMessage::setChatPartnerName(const QString &value)
{
    chatPartnerName = value;
}

int TextMessage::getSenderId() const
{
    return senderId;
}

void TextMessage::setSenderId(int value)
{
    senderId = value;
}

int TextMessage::getReceiverId() const
{
    return receiverId;
}

void TextMessage::setReceiverId(int value)
{
    receiverId = value;
}

QString TextMessage::getMessage() const
{
    return message;
}

void TextMessage::setMessage(const QString &value)
{
    message = value;
}

QString TextMessage::getSentAt() const
{
    return sentAt;
}

void TextMessage::setSentAt(const QString &value)
{
    sentAt = value;
}

TextMessage::TextMessage()
    : messageId(0), myName("username"), chatPartnerName("chatPartnerName"), senderId(0), receiverId(0), message("message"), sentAt("0000-01-01 00:00:00")
{
}

// Parameterized constructor
TextMessage::TextMessage(int messageId, const QString &myName, const QString &chatPartnerName,
                         int senderId, int receiverId, const QString &message, const QString &sentAt)
    : messageId(messageId), myName(myName), chatPartnerName(chatPartnerName),
      senderId(senderId), receiverId(receiverId), message(message), sentAt(sentAt)
{
}

// Copy constructor
TextMessage::TextMessage(const TextMessage &other)
    : messageId(other.messageId), myName(other.myName), chatPartnerName(other.chatPartnerName),
      senderId(other.senderId), receiverId(other.receiverId), message(other.message), sentAt(other.sentAt)
{
}

// Move constructor
TextMessage::TextMessage(TextMessage &&other) noexcept
    : messageId(other.messageId), myName(std::move(other.myName)), chatPartnerName(std::move(other.chatPartnerName)),
      senderId(other.senderId), receiverId(other.receiverId), message(std::move(other.message)), sentAt(std::move(other.sentAt))
{
    // Clear the source object
    other.messageId = 0;
    other.senderId = 0;
    other.receiverId = 0;
}

// Copy assignment operator
TextMessage& TextMessage::operator=(const TextMessage &other)
{
    if (this != &other) {
        messageId = other.messageId;
        myName = other.myName;
        chatPartnerName = other.chatPartnerName;
        senderId = other.senderId;
        receiverId = other.receiverId;
        message = other.message;
        sentAt = other.sentAt;
    }
    return *this;
}

// Move assignment operator
TextMessage& TextMessage::operator=(TextMessage &&other) noexcept
{
    if (this != &other) {
        messageId = other.messageId;
        myName = std::move(other.myName);
        chatPartnerName = std::move(other.chatPartnerName);
        senderId = other.senderId;
        receiverId = other.receiverId;
        message = std::move(other.message);
        sentAt = std::move(other.sentAt);

        // Clear the source object
        other.messageId = 0;
        other.senderId = 0;
        other.receiverId = 0;
    }
    return *this;
}

// Destructor
TextMessage::~TextMessage()
{
}

// Method to return a string representation of the message
QString TextMessage::toString() const
{
    return QString("Message ID: %1; My Name: %2; Chat Partner Name: %3; Sender ID: %4; Receiver ID: %5; Message: %6; Sent At: %7")
        .arg(messageId)
        .arg(myName)
        .arg(chatPartnerName)
        .arg(senderId)
        .arg(receiverId)
        .arg(message)
        .arg(sentAt);
}


// Builder class methods
TextMessage::Builder& TextMessage::Builder::setMessageId(int id)
{
    messageId = id;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setMyName(const QString &name)
{
    myName = name;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setChatPartnerName(const QString &name)
{
    chatPartnerName = name;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setSenderId(int id)
{
    senderId = id;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setReceiverId(int id)
{
    receiverId = id;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setMessage(const QString &msg)
{
    message = msg;
    return *this;
}

TextMessage::Builder& TextMessage::Builder::setSentAt(const QString &sentAt)
{
    this->sentAt = sentAt;
    return *this;
}

TextMessage TextMessage::Builder::build() const
{
    return TextMessage(messageId, myName, chatPartnerName, senderId, receiverId, message, sentAt);
}
