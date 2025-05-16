#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist : public SongList
{
public:
    inline QString getName()
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

#endif // PLAYLIST_H
