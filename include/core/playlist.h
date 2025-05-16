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

    inline QPixmap getCover() const
    {
        return cover;
    }

    inline void setCover(const QPixmap &value)
    {
        cover = value;
    }

private:
    QString name;
    QPixmap cover;
};

Q_DECLARE_METATYPE(Playlist)

using PlaylistGroup = QList<Playlist>;


#endif // PLAYLIST_H
