#include "../../include/models/playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent) : QAbstractListModel(parent)
{}

PlaylistModel::PlaylistModel(PlaylistModel &&data, QObject *parent) : PlaylistModel{parent}
{
    container = std::move(data);
}

PlaylistModel::PlaylistModel(const PlaylistModel &data, QObject *parent) : PlaylistModel{parent}
{
    container = data;
}

PlaylistModel &PlaylistModel::operator=(const PlaylistModel &data)
{
    beginResetModel();
    container = data.container();
    endResetModel();
    return *this;
}

PlaylistModel& PlaylistModel::operator=(PlaylistModel &&data)
{
    beginResetModel();
    data.beginResetModel();
    container = std::move(data.container());
    data.endResetModel();
    endResetModel();
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
    default:
    {
        return {};
    }
    }
}

PlaylistList &PlaylistModel::container()
{
    return container;
}

const PlaylistList &PlaylistModel::container() const
{
    return container;
}

void PlaylistModel::insertPlaylist(int row, const Playlist &target)
{
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, target);
    endInsertRows();
    emit playlistsChanged();
}

void PlaylistModel::insertPlaylist(int row, const PlaylistList &target)
{
    beginInsertRows(QModelIndex(), row, row + target.size());
    container.insert(row, target);
    endInsertRows();
    emit playlistsChanged();
}

void PlaylistModel::prependPlaylist(const Playlist &target)
{
    insertPlaylist(0, target);
}

void PlaylistModel::prependPlaylist(const PlaylistList &target)
{
    insertPlaylist(0, target);
}

void PlaylistModel::appendPlaylist(const Playlist &target)
{
    insertPlaylist(container.size(), target);
}

void PlaylistModel::appendPlaylist(const PlaylistList &target)
{
    insertPlaylist(container.size(), target);
}

void PlaylistModel::removePlaylist(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    container.remove(row);
    endRemoveRows();
    emit playlistsChanged();
}

Playlist PlaylistModel::takePlaylist(int row)
{
    Playlist container = container.at(row);
    removePlaylist(row);
    return container;
}
