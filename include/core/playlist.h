#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist : public SongList
{
public:
    enum Role
    {
        GenreTextRole = Qt::UserRole + 3,
        GenreIconRole = Qt::UserRole + 4,
        PlayingRole = Qt::UserRole + 1,
        ArtistRole = Qt::UserRole + 2,
        GenreRole = Qt::UserRole + 6,
        YearRole = Qt::UserRole + 5
    };

    QString getName() const;
    void setName(const QString &value);

    bool operator==(const Playlist &other) const;
    bool operator!=(const Playlist &other) const;

    friend QDataStream& operator>>(QDataStream &stream, Playlist &target);
    friend QDataStream& operator<<(QDataStream &stream, const Playlist &target);

private:
    QString name;
};

Q_DECLARE_METATYPE(Playlist)

using PlaylistGroup = QList<Playlist>;

QDataStream& operator>>(QDataStream &stream, Playlist &target);
QDataStream& operator<<(QDataStream &stream, const Playlist &target);

#endif // PLAYLIST_H
