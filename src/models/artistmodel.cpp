#include "include/models/artistmodel.h"

const Artist &ArtistModel::artist() const
{
    return container;
}

bool ArtistModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid() || row < 0)
    {
        return false;
    }
    beginInsertRows(parent, row, row + count - 1);
    for(int i = 0; i < count; ++i)
    {
        container.insert(row, Playlist());
    }
    endInsertRows();
    return true;
}

bool ArtistModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid() || row < 0)
    {
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    container.remove(row, count);
    endRemoveRows();
    return true;
}

int ArtistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

bool ArtistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        switch(role)
        {
            case Artist::NameRole:
            {
                container.setName(value.toString());
                emit dataChanged(index, index, {role});
                return true;
            }
            case Artist::BiographyRole:
            {
                container.setBiography(value.toString());
                emit dataChanged(index, index, {role});
                return true;
            }
            case Artist::PhotoRole:
            {
                container.setPhoto(value.value<QPixmap>());
                emit dataChanged(index, index, {role});
                return true;
            }
            default:
            {
                return false;
            }
        }
    }
    switch(role)
    {
        case Qt::DisplayRole:
        {
            Playlist target = container.at(index.row());
            target.setName(value.toString());
            container.replace(index.row(), target);
            emit dataChanged(index, index, {role});
            return true;
        }
        case Qt::UserRole:
        {
            container.replace(index.row(), value.value<Playlist>());
            emit dataChanged(index, index, {role, Qt::DisplayRole, Qt::DecorationRole});
            return true;
        }
        default:
        {
            return false;
        }
    }
}

QVariant ArtistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        switch(role)
        {
            case Artist::NameRole:
            {
                return container.getName();
            }
            case Artist::BiographyRole:
            {
                return container.getBiography();
            }
            case Artist::PhotoRole:
            {
                return container.getPhoto();
            }
            default:
            {
                return QVariant();
            }
        }
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

void ArtistModel::insertPlaylist(int row, const Playlist &target)
{
    if(insertRow(row))
    {
        setData(index(row), QVariant::fromValue(target), Qt::UserRole);
    }
}

void ArtistModel::insertPlaylist(int row, const PlaylistGroup &target)
{
    if(insertRows(row, target.size(), QModelIndex()))
    {
        for(int i = 0; i < target.size(); ++i)
        {
            container[i + row] = target.at(i);
        }
        emit dataChanged(index(row), index(row + target.size() - 1), {Qt::UserRole, Qt::DisplayRole, Qt::DecorationRole});
    }
}

void ArtistModel::prependPlaylist(const Playlist &target)
{
    insertPlaylist(0, target);
}

void ArtistModel::prependPlaylist(const PlaylistGroup &target)
{
    insertPlaylist(0, target);
}

void ArtistModel::appendPlaylist(const Playlist &target)
{
    insertPlaylist(container.size(), target);
}

void ArtistModel::appendPlaylist(const PlaylistGroup &target)
{
    insertPlaylist(container.size(), target);
}

void ArtistModel::removePlaylist(int row)
{
    removeRow(row);
}

void ArtistModel::setName(const QString &value)
{
    setData({}, value, Artist::NameRole);
}

void ArtistModel::setPhoto(const QPixmap &value)
{
    setData({}, value, Artist::PhotoRole);
}

void ArtistModel::setBiography(const QString &value)
{
    setData({}, value, Artist::BiographyRole);
}
