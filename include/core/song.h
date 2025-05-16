#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QUrl>

class Song : public QObject
{
    Q_OBJECT
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
    Q_ENUM(Genre)

public:
    explicit Song(QObject *parent = nullptr);
    Song(const Song &other, QObject *parent = nullptr);
    Song(Song &&other, QObject *parent = nullptr) noexcept;
    ~Song() override;

    Song& operator=(const Song &other);
    Song& operator=(Song&& other);

    Genre getGenre() const;
    QUrl getAddress() const;
    QString getName() const;
    QString getArtist() const;
    int getPublicationYear() const;
    
    friend bool operator==(const Song &one, const Song &two);
    friend bool operator!=(const Song &one, const Song &two);

    friend QDebug operator<<(QDebug debug, const Song &song);
    friend QDataStream& operator<<(QDataStream &stream, const Song &another);
    friend QDataStream& operator>>(QDataStream &stream, Song &another);

public slots:
    void setGenre(Genre value);
    void setName(const QString &value);
    void setArtist(const QString &value);
    void setPublicationYear(int value);
    void setAddress(const QUrl &value);

signals:
    void nameChanged(QString name);
    void genreChanged(Genre genre);
    void addressChanged(QUrl address);
    void artistChanged(QString artist);
    void publicationYearChanged(int year);

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
