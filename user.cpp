#include "user.h"

User::User(QString username, QString type, QObject *parent)
    : QObject(parent), _username(username), _type(type)
{

}

QString User::username() const
{
    return _username;
}

void User::setUsername(const QString &username)
{
    _username = username;
}

QString User::type() const
{
    return _type;
}

void User::setType(const QString &type)
{
    _type = type;
}
