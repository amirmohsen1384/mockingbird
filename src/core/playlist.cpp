#include "include/core/playlist.h"

Playlist::Playlist() {}


QString Playlist::getName() const
{
    return name;
}

void Playlist::setName(const QString &value)
{
    name = value;
    emit nameChanged(value);
}

