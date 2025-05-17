#include "include/core/playlist.h"
#include <QDataStream>

QString Playlist::getName() const
{
    return name;
}

void Playlist::setName(const QString &value)
{
    name = value;
}

QPixmap Playlist::getCover() const
{
    return cover;
}

void Playlist::setCover(const QPixmap &value)
{
    cover = value;
}

bool Playlist::operator==(const Playlist &other) const
{
    if(this->name != other.name)
    {
        return false;
    }
    else if(this->cover.toImage() != other.cover.toImage())
    {
        return false;
    }
    else if(static_cast<SongList>(*this) != static_cast<SongList>(other))
    {
        return false;
    }
    return true;
}

bool Playlist::operator!=(const Playlist &other) const
{
    return !(*this == other);
}

QDataStream& operator<<(QDataStream &stream, const Playlist &target)
{
    stream << target.name;
    stream << target.cover;
    stream << static_cast<SongList>(target);
    return stream;
}

QDataStream& operator>>(QDataStream &stream, Playlist &target)
{
    stream >> target.name;
    stream >> target.cover;
    stream >> static_cast<SongList&>(target);
    return stream;
}
