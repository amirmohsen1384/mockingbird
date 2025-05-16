#ifndef SONG_H
#define SONG_H

#include <QUrl>
#include <QVariant>

class Song
{
public:
    enum Genre
    {
        Rock,
        Rap,
        Pop,
        Jazz,
        Electronic,
        Classic,
        Folk,
        Country
    };

public:
    Song() = default;
    Song(const Song &other);
    Song(Song &&other) noexcept;

    Song& operator=(const Song &other);
    Song& operator=(Song&& other);

    Genre getGenre() const;
    QUrl getAddress() const;
    QString getName() const;
    QString getArtist() const;
    int getPublicationYear() const;
    
    friend bool operator==(const Song &one, const Song &two);
    friend bool operator!=(const Song &one, const Song &two);

    friend QDataStream& operator<<(QDataStream &stream, const Song &another);
    friend QDataStream& operator>>(QDataStream &stream, Song &another);

public:
    void setArtist(const QString &value);
    void setName(const QString &value);
    void setPublicationYear(int value);
    void setAddress(const QUrl &value);
    void setGenre(Genre value);

private:
    QUrl address;
    QString name;
    QString artist;
    int publicationYear;
    Genre genre = Genre::Classic;
};

bool operator==(const Song &one, const Song &two);
bool operator!=(const Song &one, const Song &two);

QDataStream& operator<<(QDataStream &stream, const Song &another);
QDataStream& operator>>(QDataStream &stream, Song &another);

Q_DECLARE_METATYPE(Song)

using SongList = QList<Song>;

#endif // SONG_H
