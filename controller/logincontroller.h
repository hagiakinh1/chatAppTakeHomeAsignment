#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include<model/dataaccessobject.h>
#include"navigator.h"
class LoginController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notificationText READ notificationText WRITE setNotificationText NOTIFY notificationTextChanged)
public:
    explicit LoginController(QObject *parent = nullptr);
    Q_INVOKABLE login(QString userName, QString password);
    Q_INVOKABLE signUp(QString userName, QString password);
    void verifyLogin();

    QString notificationText() const
    {
        return m_notificationText;
    }
    Q_INVOKABLE int getUserId();
    QString getUserName() const;

signals:

    void notificationTextChanged(QString notificationText);
    void userChanged(int user_id);
public slots:
void setNotificationText(QString notificationText)
{
    if (m_notificationText == notificationText)
        return;

    m_notificationText = notificationText;
    emit notificationTextChanged(m_notificationText);
}

private:
    QString userName;
    QString password;
    QString m_notificationText;
    int user_id ;
    void setUserId(int user_id);
};

#endif // LOGINCONTROLLER_H
