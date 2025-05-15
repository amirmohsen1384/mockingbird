#include "include/core/person.h"
#include <QRegularExpression>

Person::Person(QObject *parent) : QObject{parent} {}

Person::Person(const Person &another, QObject *parent) : Person{parent}
{
    *this = another;
}

Person::Person(Person &&another, QObject *parent) : Person{parent}
{
    *this = std::move(another);
}

Person &Person::operator=(const Person &another)
{
    firstName = another.firstName;
    lastName = another.lastName;
    userName = another.userName;
    password = another.password;
    return *this;
}

Person& Person::operator=(Person &&another)
{
    firstName = std::move(another.firstName);
    lastName = std::move(another.lastName);
    userName = std::move(another.userName);
    password = std::move(another.password);
    return *this;
}

QString Person::getFirstName() const
{
    return firstName;
}

QString Person::getUserName() const
{
    return userName;
}

QString Person::getLastName() const
{
    return lastName;
}

QString Person::getPassword() const
{
    return password;
}

bool Person::setFirstName(const QString &value)
{
    // Matches only with values that has no non-letter characters.
    QRegularExpression pattern("[a-zA-Z ]{6,}");

    // Checks if the given values matches with the regex.
    if(pattern.match(value).hasMatch())
    {
        firstName = value;
        emit firstNameChanged(firstName);
        return true;
    }
    else
    {
        return false;
    }
}

bool Person::setLastName(const QString &value)
{
    // Matches only with values that has no non-letter characters.
    QRegularExpression pattern("[a-zA-Z ]{6,}");

    // Checks if the given values matches with the regex.
    if(pattern.match(value).hasMatch())
    {
        lastName = value;
        emit lastNameChanged(lastName);
        return true;
    }
    else
    {
        return false;
    }
}

bool Person::setUserName(const QString &value)
{
    // Matches only with values with at least 6 characters.
    QRegularExpression pattern(".{6,}");

    // Checks if the given values matches with the regex.
    if(pattern.match(value).hasMatch())
    {
        userName = value;
        emit userNameChanged(userName);
        return true;
    }
    else
    {
        return false;
    }
}

bool Person::setPassword(const QString &value)
{
    /* Matches only with values with
     * at least 8 characters
     * one uppercase letter
     * one lowercase letter
     * one non-character letter
     * one number
    */
    QRegularExpression pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[\\W_])[A-Za-z\\d\\W_]{8,}$");

    // Checks if the given values matches with the regex.
    if(pattern.match(value).hasMatch())
    {
        password = value;
        emit passwordChanged(password);
        return true;
    }
    else
    {
        return false;
    }
}

QDataStream& operator<<(QDataStream &stream, const Person &data)
{
    stream << data.firstName << data.lastName;
    stream << data.userName << data.password;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Person &data)
{
    stream >> data.firstName >> data.lastName;
    stream >> data.userName >> data.password;
    return stream;
}
