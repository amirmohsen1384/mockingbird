#include "include/core/song.h"
#include <QDataStream>
#include <QDebug>
#include <QUrl>

Song& Song::operator=(const Song &another)
{
    name = another.name;
    genre = another.genre;
    artist = another.artist;
    address = another.address;
    publicationYear = another.publicationYear;
    return *this;
}

Song& Song::operator=(Song &&another)
{
    name = std::move(another.name);
    genre = std::move(another.genre);
    artist = std::move(another.artist);
    address = std::move(another.address);
    publicationYear = std::move(another.publicationYear);
    return *this;
}

Song::Song(const Song &other)
{
    *this = other;
}
Song::Song(Song &&other) noexcept
{
    *this = std::move(other);
}

bool operator==(const Song &one, const Song &two)
{
    if(one.name != two.name) {
        return false;
    }
    else if(one.genre != two.genre) {
        return false;
    }
    else if(one.artist != two.artist) {
        return false;
    }
    else if(one.publicationYear != two.publicationYear) {
        return false;
    }
    else if(one.address != two.address) {
        return false;
    }
    else {
        return true;
    }
}

bool operator!=(const Song &one, const Song &two)
{
    return !(one == two);
}

QString Song::getName() const
{
    return name;
}

Song::Genre Song::getGenre() const
{
    return genre;
}

QString Song::getArtist() const
{
    return artist;
}

int Song::getPublicationYear() const
{
    return publicationYear;
}

QUrl Song::getAddress() const
{
    return address;
}

void Song::setName(const QString &value)
{
    name = value;
}

void Song::setGenre(Genre value)
{
    genre = value;
}
void Song::setArtist(const QString &value)
{
    artist = value;
}
void Song::setPublicationYear(int value)
{
    publicationYear = value;
}
void Song::setAddress(const QUrl &value)
{
    address = value;
}

QDataStream& operator<<(QDataStream &stream, const Song &another)
{
    stream << another.name;
    stream << another.genre;
    stream << another.artist;
    stream << another.address;
    stream << another.publicationYear;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Song &another)
{
    stream >> another.name;
    stream >> another.genre;
    stream >> another.artist;
    stream >> another.address;
    stream >> another.publicationYear;
    return stream;
}
