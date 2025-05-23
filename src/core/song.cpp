#include "include/core/song.h"
#include <QDataStream>

QString Song::getName() const
{
    return name;
}

QPixmap Song::getCover() const
{
    return cover;
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

bool Song::operator==(const Song &other) const
{
    if(this->name != other.name)
    {
        return false;
    }
    else if(this->genre != other.genre)
    {
        return false;
    }
    else if(this->artist != other.artist)
    {
        return false;
    }
    else if(this->publicationYear != other.publicationYear)
    {
        return false;
    }
    else if(this->address != other.address)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Song::operator!=(const Song &other) const
{
    return !(*this == other);
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

void Song::setCover(const QPixmap &value)
{
    cover = value;
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
