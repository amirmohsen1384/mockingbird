#include "include/models/playlistmodel.h"
#include "include/models/genremodel.h"
#include <QPixmap>
#include <QFont>

const QVector<int> PlaylistModel::roles  =
{
    Qt::UserRole,
    Qt::DisplayRole,
    Qt::DecorationRole,
    Playlist::ArtistRole,
    Playlist::GenreRole,
    Playlist::YearRole
};

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return container.size();
}

bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        switch(role)
        {
        case Qt::DisplayRole:
        {
            container.setName(value.toString());
            emit dataChanged(index, index, {Qt::DisplayRole});
            return true;
        }
        case Playlist::PlayingRole:
        {
            current = value.toInt();
            emit dataChanged(index, index, {Playlist::PlayingRole, Qt::BackgroundRole, Qt::FontRole});
            return true;
        }
        default:
        {
            return false;
        }
        }
    }

    Song &target = container[index.row()];

    switch(role)
    {
    case Qt::DisplayRole:
    {
        target.setName(value.toString());
        emit dataChanged(index, index, {Qt::DisplayRole});
        return true;
    }
    case Qt::DecorationRole:
    {
        target.setCover(value.value<QPixmap>());
        emit dataChanged(index, index, {Qt::DecorationRole});
        return true;
    }
    case Playlist::ArtistRole:
    {
        target.setArtist(value.toString());
        emit dataChanged(index, index, {Playlist::ArtistRole});
        return true;
    }
    case Playlist::GenreRole:
    {
        target.setGenre(qvariant_cast<Song::Genre>(value));
        emit dataChanged(index, index, {Playlist::GenreRole});
        return true;
    }
    case Playlist::YearRole:
    {
        target.setPublicationYear(value.toInt());
        emit dataChanged(index, index, {Playlist::YearRole});
        return true;
    }
    case Qt::UserRole:
    {
        container.replace(index.row(), qvariant_cast<Song>(value));
        emit dataChanged(index, index, roles);
        return true;
    }
    default:
    {
        return false;
    }
    }
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        switch(role)
        {
        case Qt::DisplayRole:
        {
            return container.getName();
        }
        case Playlist::PlayingRole:
        {
            return current;
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
    case Qt::BackgroundRole:
    {
        return index.row() == current ? QColor(217, 255, 161) : QVariant();
    }
    case Qt::FontRole:
    {
        return index.row() == current ? QFont("Segoe UI", 10, QFont::Bold) : QVariant();
    }
    case Qt::DecorationRole:
    {
        if(target.getCover().isNull())
        {
            return QPixmap(":/images/playlist/song.png").scaled(64, 64);
        }
        else
        {
            return target.getCover().scaled(QSize(64, 64), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue<Song>(target);
    }
    case Playlist::PlayingRole:
    {
        return index.row() == this->current;
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

void PlaylistModel::setName(const QString &name)
{
    setData(QModelIndex(), name, Qt::DisplayRole);
}

void PlaylistModel::setCurrentTrack(qint64 value)
{
    setData(QModelIndex(), value, Playlist::PlayingRole);
}

PlaylistModel::PlaylistModel(const Playlist &initial, QObject *parent) : PlaylistModel(parent)
{
    setPlaylist(initial);
}

QString PlaylistModel::name() const
{
    return container.getName();
}

qint64 PlaylistModel::currentTrack() const
{
    return current;
}

const Playlist &PlaylistModel::playlist() const
{
    return container;
}

void PlaylistModel::setPlaylist(const Playlist &value)
{
    beginResetModel();
    container = value;
    current = -1;
    endResetModel();
}

bool PlaylistModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for(int index = 0; index < count; ++index)
    {
        container.insert(row, Song());
    }
    endInsertRows();
    return true;
}

bool PlaylistModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    container.remove(row, count);
    endRemoveRows();
    return true;
}

void PlaylistModel::insertSong(int row, const Song &target)
{
    insertRow(row);
    setData(index(row), QVariant::fromValue(target), Qt::UserRole);
}

void PlaylistModel::insertSong(int row, const SongList &target)
{
    const int size = target.size();
    insertRows(row, size, QModelIndex());
    for(int i = row; i < row + size; ++i)
    {
        container[i] = target.at(i - row);
    }
    emit dataChanged(index(row), index(row + size), roles);
}

void PlaylistModel::appendSong(const Song &target)
{
    insertSong(rowCount(), target);
}

void PlaylistModel::appendSong(const SongList &target)
{
    insertSong(rowCount(), target);
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
    removeRow(row);
}
