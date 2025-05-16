#include "include/core/song.h"
#include <QDataStream>
#include <QDebug>
#include <QUrl>

Song::Song(QObject *parent) : QObject{parent} {}

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

    publicationYear = 0;
    genre = Genre::Classic;
    return *this;
}

Song::Song(const Song &other, QObject *parent) : Song(parent)
{
    *this = other;
}
Song::Song(Song &&other, QObject *parent) noexcept : Song(parent)
{
    *this = std::move(other);
}

Song::~Song() {}

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
    if (name != value) {
        name = value;
        emit nameChanged(name);
    }
}
void Song::setGenre(Genre value)
{
    if (genre != value) {
        genre = value;
        emit genreChanged(genre);
    }
}
void Song::setArtist(const QString &value)
{
    if (artist != value) {
        artist = value;
        emit artistChanged(artist);
    }
}
void Song::setPublicationYear(int value)
{
    if (publicationYear != value) {
        publicationYear = value;
        emit publicationYearChanged(publicationYear);
    }
}
void Song::setAddress(const QUrl &value)
{
    if (address != value) {
        address = value;
        emit addressChanged(address);
    }
}

QDataStream& operator<<(QDataStream &stream, const Song &another)
{
    stream << another.name;
    stream << another.genre;
    stream << another.artist;
    stream << another.publicationYear;
    stream << another.address;
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Song &another)
{
    stream >> another.name;
    stream >> another.genre;
    stream >> another.artist;
    stream >> another.publicationYear;
    stream >> another.address;
    return stream;
}

QDebug operator<<(QDebug debug, const Song &song)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "Song(";
    debug.nospace() << "name: " << song.getName() << ", ";
    debug.nospace() << "genre: " << song.getGenre() << ", ";
    debug.nospace() << "artist: " << song.getArtist() << ", ";
    debug.nospace() << "publicationYear: " << song.getPublicationYear() << ", ";
    debug.nospace() << "address: " << song.getAddress();
    debug.nospace() << ")";
    return debug;
}
