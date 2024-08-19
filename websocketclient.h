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
    explicit WebsocketClient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

    void onDisconnected();
    void handleExit();
    void handleNewInput(const QString &input);
signals:
    void closed();
public slots:
    void sendTextMessage(QString message);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    bool m_isConnected = false;
};

#endif // ECHOCLIENT_H
