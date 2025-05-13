#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QUrl>

class Song : public QObject
{
    Q_OBJECT
public:
    explicit Song(QObject *parent = nullptr);
    Song(const Song &other, QObject *parent = nullptr);
    Song(Song &&other, QObject *parent = nullptr) noexcept;

    Song& operator=(const Song &other);
    Song& operator=(Song&& other);

    QUrl getAddress() const;
    QString getName() const;
    QString getGenre() const;
    QString getArtist() const;
    int getPublicationYear() const;
    
    friend bool operator==(const Song &one, const Song &two);
    friend bool operator!=(const Song &one, const Song &two);

    friend QDebug operator<<(QDebug debug, const Song &song);
    friend QDataStream& operator<<(QDataStream &stream, const Song &another);
    friend QDataStream& operator>>(QDataStream &stream, Song &another);

public slots:
    void setName(const QString &value);
    void setGenre(const QString &value);
    void setArtist(const QString &value);
    void setPublicationYear(int value);
    void setAddress(const QUrl &value);

signals:
    void nameChanged(QString name);
    void genreChanged(QString genre);
    void addressChanged(QUrl address);
    void artistChanged(QString artist);
    void publicationYearChanged(int year);

private:
    QUrl address;
    QString name;
    QString genre;
    QString artist;
    int publicationYear;
};

bool operator==(const Song &one, const Song &two);
bool operator!=(const Song &one, const Song &two);

QDataStream& operator<<(QDataStream &stream, const Song &another);
QDataStream& operator>>(QDataStream &stream, Song &another);

Q_DECLARE_METATYPE(Song)

using SongList = QList<Song>;

#endif // SONG_H
