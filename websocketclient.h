#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QSocketNotifier>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QByteArray>
class WebsocketClient : public QObject
{
    Q_OBJECT
public:
    static WebsocketClient& getInstance();

    WebsocketClient(const WebsocketClient&) = delete;
    WebsocketClient& operator=(const WebsocketClient&) = delete;
    void onDisconnected();
    void handleExit();
    void handleNewInput(const QString &input);
    void sendTextMessage(QString senderName, QString receiverName, QString message, int senderId, int receiverId);
    ~WebsocketClient();
signals:
    void closed();
public slots:

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    bool m_isConnected = false;
    explicit WebsocketClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

};

#endif // ECHOCLIENT_H
