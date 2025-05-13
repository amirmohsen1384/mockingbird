#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "song.h"

class Playlist : public SongList
{
public:
    QString getName() const;

public slots:
    void setName(const QString &value);

signals:
    void nameChanged(const QString &value);
    
private:
    QString name;
};

#endif // PLAYLIST_H
