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
    Genre getGenre() const;
    QUrl getAddress() const;
    QString getName() const;
    QPixmap getCover() const;
    QString getArtist() const;
    int getPublicationYear() const;
    
    friend bool operator==(const Song &one, const Song &two);
    friend bool operator!=(const Song &one, const Song &two);

    friend QDataStream& operator<<(QDataStream &stream, const Song &another);
    friend QDataStream& operator>>(QDataStream &stream, Song &another);

public:
    void setArtist(const QString &value);
    void setCover(const QPixmap &value);
    void setName(const QString &value);
    void setPublicationYear(int value);
    void setAddress(const QUrl &value);
    void setGenre(Genre value);

private:
    QUrl address;
    QString name;
    QPixmap cover;
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
