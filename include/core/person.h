#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include "general.h"

class Person
{
public:
    QString getFirstName() const;
    QString getUserName() const;
    QString getLastName() const;
    QString getPassword() const;

    bool setFirstName(const QString &value);
    bool setLastName(const QString &value);
    bool setUserName(const QString &value);
    bool setPassword(const QString &value);

    virtual bool saveToRecord() = 0;

    friend QDataStream& operator<<(QDataStream &stream, const Person &data);
    friend QDataStream& operator>>(QDataStream &stream, Person &data);

protected:
    QString firstName;
    QString lastName;
    QString userName;
    QString password;
};

Q_DECLARE_METATYPE(Person)

QDataStream& operator<<(QDataStream &stream, const Person &data);
QDataStream& operator>>(QDataStream &stream, Person &data);

#endif // PERSON_H
