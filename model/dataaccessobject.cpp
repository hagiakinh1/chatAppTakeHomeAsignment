#include "dataaccessobject.h"
bool DataAccessObject::createMessagesTable() {
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Messages (
            message_id INTEGER PRIMARY KEY AUTOINCREMENT,
            sender_id INTEGER NOT NULL,
            receiver_id INTEGER NOT NULL,
            message_text TEXT NOT NULL,
            sent_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (sender_id) REFERENCES Users(user_id),
            FOREIGN KEY (receiver_id) REFERENCES Users(user_id)
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug( "Failed to create Messages table:" + query.lastError().text().toLatin1());
        return false;
    }

    return true;
}
bool DataAccessObject::createUsersTable() {
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS Users (
            user_id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT NOT NULL UNIQUE,
            password_hash TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    )";

    if (!query.exec(createTableQuery)) {
        qDebug("Failed to create Users table:" + query.lastError().text().toLatin1());
        return false;
    }

    return true;
}

DataAccessObject::DataAccessObject()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("C:/sqlite/chatAppDB.db");
    if (!m_db.open())
    {
        qDebug( "Error: connection with database failed");
    }
    else
    {
      qDebug( "Database: connection ok");
      createUsersTable();
      createMessagesTable();
    }
}

DataAccessObject::~DataAccessObject() {
    qDebug( "Database: disconnect ");
    m_db.close();
}

// Initialize the singleton instance
DataAccessObject& DataAccessObject::getInstance() {
    static DataAccessObject instance;
    return instance;
}


bool DataAccessObject::createUser(const QString& username, const QString& password_hash) {
    QSqlQuery query;

    query.prepare("INSERT INTO Users (username, password_hash) VALUES (:username, :password_hash)");
    query.bindValue(":username", username);
    query.bindValue(":password_hash", password_hash);

    if (!query.exec()) {
        qDebug( "Error: Could not insert user into Users table -" );
        return false;
    }

    return true;
}

QList<QVariantList> DataAccessObject::readAllUsers() {
    QSqlQuery query("SELECT user_id, username, password_hash, created_at FROM Users");

    QList<QVariantList> users;

    while (query.next()) {
        QVariantList user;
        user << query.value("user_id")
             << query.value("username")
             << query.value("password_hash")
             << query.value("created_at");
        users.append(user);
    }

    return users;
}


bool DataAccessObject::updateUser(int user_id, const QString& newUsername, const QString& newPasswordHash) {
    QSqlQuery query;

    query.prepare("UPDATE Users SET username = :username, password_hash = :password_hash WHERE user_id = :user_id");
    query.bindValue(":username", newUsername);
    query.bindValue(":password_hash", newPasswordHash);
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug("Error: Could not update user -" + query.lastError().text().toLatin1());
        return false;
    }

    return true;
}


bool DataAccessObject::deleteUser(int user_id) {
    QSqlQuery query;

    query.prepare("DELETE FROM Users WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);

    if (!query.exec()) {
        qDebug("Error: Could not delete user -" + query.lastError().text().toLatin1());
        return false;
    }

    return true;
}

bool DataAccessObject::createMessage(int sender_id, int receiver_id, const QString& message_text) {
    QSqlQuery query;

    query.prepare("INSERT INTO Messages (sender_id, receiver_id, message_text) "
                  "VALUES (:sender_id, :receiver_id, :message_text)");
    query.bindValue(":sender_id", sender_id);
    query.bindValue(":receiver_id", receiver_id);
    query.bindValue(":message_text", message_text);

    if (!query.exec()) {
        qDebug( "Error: Could not insert message into Messages table -" + query.lastError().text().toLatin1());
        return false;
    }

    return true;
}


QList<QVariantList> DataAccessObject::readMessagesBetweenUsers(int user1_id, int user2_id) {
    QSqlQuery query;
    query.prepare("SELECT message_id, sender_id, receiver_id, message_text, sent_at FROM Messages "
                  "WHERE (sender_id = :user1_id AND receiver_id = :user2_id) "
                  "OR (sender_id = :user2_id AND receiver_id = :user1_id) "
                  "ORDER BY sent_at");

    query.bindValue(":user1_id", user1_id);
    query.bindValue(":user2_id", user2_id);

    QList<QVariantList> messages;

    if (query.exec()) {
        while (query.next()) {
            QVariantList message;
            message << query.value("message_id")
                    << query.value("sender_id")
                    << query.value("receiver_id")
                    << query.value("message_text")
                    << query.value("sent_at");
            messages.append(message);
        }
    } else {
        qDebug( "Error: Could not retrieve messages -" + query.lastError().text().toLatin1());
    }

    return messages;
}



