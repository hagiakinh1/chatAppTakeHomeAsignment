
#include "websocketclient.h"
#include <QtCore/QDebug>


WebsocketClient::WebsocketClient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &WebsocketClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebsocketClient::onDisconnected);
    m_webSocket.open(QUrl(url));

}

void WebsocketClient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &WebsocketClient::onTextMessageReceived);
    m_isConnected = true;
}

void WebsocketClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    emit textMessageReceivedDelegate(message);
}
WebsocketClient &WebsocketClient::getInstance()
{
    static WebsocketClient mWebsocketClient(QUrl("ws://localhost:1234"), true);
    return mWebsocketClient;
}


void WebsocketClient::onDisconnected()
{
    if (m_debug)
        qDebug() << "WebSocket disconnected";

    m_isConnected = false;
    emit closed();
    m_webSocket.close();

}
void WebsocketClient::sendTextMessage(QString senderName, QString receiverName, QString message, int senderId, int receiverId)
{   if (m_isConnected)
    {

        // Create a JSON object
        QJsonObject jsonObject;
        jsonObject["senderName"] = senderName;
        jsonObject["receiverName"] = receiverName;
        jsonObject["message"] = message;
        jsonObject["senderId"] = senderId;
        jsonObject["receiverId"] = receiverId;

        // Convert JSON object to JSON document
        QJsonDocument jsonDoc(jsonObject);

        // Convert JSON document to JSON text (QByteArray)
        QByteArray jsonText = jsonDoc.toJson(QJsonDocument::Compact);

        // If you need the JSON text as a QString
        QString jsonString = QString::fromUtf8(jsonText);
        m_webSocket.sendTextMessage(jsonString);
    }
    else
    {
        qDebug("webSocket is not connected");
    }
}

WebsocketClient::~WebsocketClient()
{
    m_webSocket.close();
}


void WebsocketClient::handleNewInput(const QString &input) {
    qDebug() << "You entered:" << input;
//    sendTextMessage(input);
}

void WebsocketClient::handleExit() {
    qDebug("Exiting application...");
    m_webSocket.close();
}
