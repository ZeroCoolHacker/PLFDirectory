#ifndef USER_H
#define USER_H

#include <QObject>
#include <QString>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString username, QString type, QObject *parent = nullptr);

    QString username() const;
    void setUsername(const QString &username);

    QString type() const;
    void setType(const QString &type);


signals:

public slots:

private:
    QString _username, _type;
    enum ACCOUNT_TYPE  {
        ADMIN, MANAGER, STANDARD
    };
    QString types[3] = {"admin", "manager", "standard"};
};

#endif // USER_H
