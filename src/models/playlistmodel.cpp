#include "include/models/playlistmodel.h"
#include "include/models/genremodel.h"
#include <QPixmap>
#include <QFont>

QString PlaylistModel::getName() const
{
    return container.getName();
}

QPixmap PlaylistModel::getCover() const
{
    return container.getCover();
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        // We provide some meta-information about the playlist when the supplied index is invalid.
        switch(role)
        {
        case Qt::DisplayRole:
        {
            return container.getName();
        }
        case Qt::DecorationRole:
        {
            return container.getCover();
        }
        case Qt::UserRole:
        {
            return QVariant::fromValue(container);
        }
        default:
        {
            return {};
        }
        }
    }

    const Song target = container.at(index.row());

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return target.getName();
    }
    case Qt::DecorationRole:
    {
        if(target.getCover().isNull())
        {
            return QPixmap(":/images/playlist/song.png");
        }
        else
        {
            return target.getCover();
        }
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue<Song>(target);
    }
    case Playlist::ArtistRole:
    {
        return target.getArtist();
    }
    case Playlist::GenreRole:
    {
        return QVariant::fromValue(target.getGenre());
    }
    case Playlist::GenreTextRole:
    {
        return GenreModel::toString(target.getGenre());
    }
    case Playlist::GenreIconRole:
    {
        return GenreModel::toPixmap(target.getGenre());
    }
    case Playlist::YearRole:
    {
        return target.getPublicationYear();
    }
    default:
    {
        return {};
    }
    }
}

void PlaylistModel::insertSong(int row, const Song &target)
{
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, target);
    endInsertRows();
    emit songsChanged();
}

void PlaylistModel::insertSong(int row, const SongList &target)
{
    beginInsertRows(QModelIndex(), row, row + target.size());
    for(const Song &element : target)
    {
        container.insert(row, element);
    }
    endInsertRows();
    emit songsChanged();
}

void PlaylistModel::appendSong(const Song &target)
{
    insertSong(container.size(), target);
}

void PlaylistModel::appendSong(const SongList &target)
{
    insertSong(container.size(), target);
}

void PlaylistModel::prependSong(const Song &target)
{
    insertSong(0, target);
}

void PlaylistModel::prependSong(const SongList &target)
{
    insertSong(0, target);
}

void PlaylistModel::removeSong(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    container.remove(row);
    emit songsChanged();
    endRemoveRows();
}

void PlaylistModel::setName(const QString &name)
{
    container.setName(name);
    emit nameChanged(name);
}

void PlaylistModel::setCover(const QPixmap &value)
{
    container.setCover(value);
    emit coverChanged(value);
}

const Playlist &PlaylistModel::getPlaylist() const
{
    return container;
}
