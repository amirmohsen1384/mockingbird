#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist : public SongList
{
public:
    enum Role
    {
        GenreIconRole = Qt::UserRole + 4,
        PlayingRole = Qt::UserRole + 1,
        ArtistRole = Qt::UserRole + 2,
        GenreRole = Qt::UserRole + 3,
        YearRole = Qt::UserRole + 5
    };

    inline QString getName() const
    {
        return name;
    }

    inline void setName(const QString &value)
    {
        name = value;
    }

private:
    QString name;
};

Q_DECLARE_METATYPE(Playlist)

using Playlists = QList<Playlist>;


#endif // PLAYLIST_H
