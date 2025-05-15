#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person : public QObject
{
    Q_OBJECT
public:
    explicit Person(QObject *parent = nullptr);
    Person(Person &&another, QObject *parent = nullptr);
    Person(const Person &another, QObject *parent = nullptr);

    Person& operator=(const Person &another);
    Person& operator=(Person &&another);

    QString getFirstName() const;
    QString getUserName() const;
    QString getLastName() const;
    QString getPassword() const;

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);

public slots:
    bool setFirstName(const QString &value);
    bool setLastName(const QString &value);
    bool setUserName(const QString &value);
    bool setPassword(const QString &value);

signals:
    void firstNameChanged(const QString &value);
    void lastNameChanged(const QString &value);
    void userNameChanged(const QString &value);
    void passwordChanged(const QString &value);

private:
    QString firstName;
    QString lastName;
    QString userName;
    QString password;
};

Q_DECLARE_METATYPE(Person)

QDataStream& operator<<(QDataStream &stream, const Person &data);
QDataStream& operator>>(QDataStream &stream, Person &data);

#endif // PERSON_H
