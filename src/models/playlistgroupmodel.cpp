#include "include/models/playlistgroupmodel.h"

int PlaylistGroupModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

QVariant PlaylistGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }
    const Playlist &target = container.at(index.row());
    switch(role)
    {
    case Qt::DisplayRole:
    {
        return target.getName();
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue(target);
    }
    case Qt::DecorationRole:
    {
        QPixmap cover;
        if(!target.isEmpty())
        {
            cover = target.constFirst().getCover();
        }
        if(cover.isNull())
        {
            return QPixmap(":/images/playlist/playlist.png").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        else
        {
            return cover.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
    default:
    {
        return {};
    }
    }
}

PlaylistGroup &PlaylistGroupModel::playlists()
{
    return container;
}

const PlaylistGroup &PlaylistGroupModel::playlists() const
{
    return container;
}

void PlaylistGroupModel::insertPlaylist(int row, const Playlist &target)
{
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, target);
    endInsertRows();
    emit playlistsChanged();
}

void PlaylistGroupModel::insertPlaylist(int row, const PlaylistGroup &target)
{
    beginInsertRows(QModelIndex(), row, row + target.size());
    for(const Playlist &playlist : target)
    {
        container.insert(row, playlist);
    }
    endInsertRows();
    emit playlistsChanged();
}

void PlaylistGroupModel::prependPlaylist(const Playlist &target)
{
    insertPlaylist(0, target);
}

void PlaylistGroupModel::prependPlaylist(const PlaylistGroup &target)
{
    insertPlaylist(0, target);
}

void PlaylistGroupModel::appendPlaylist(const Playlist &target)
{
    insertPlaylist(container.size(), target);
}

void PlaylistGroupModel::appendPlaylist(const PlaylistGroup &target)
{
    insertPlaylist(container.size(), target);
}

void PlaylistGroupModel::removePlaylist(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    container.remove(row);
    endRemoveRows();
    emit playlistsChanged();
}
