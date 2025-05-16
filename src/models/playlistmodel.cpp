#include "include/models/playlistmodel.h"
#include <QPainter>
#include <QPixmap>

Playlist::Playlist(QObject *parent) : QAbstractListModel(parent)
{
    current = 0;
}

Playlist::Playlist(Playlist &&data, QObject *parent) : Playlist(parent)
{
    *this = std::move(data);
}

Playlist::Playlist(const Playlist &data, QObject *parent) : Playlist(parent)
{
    *this = data;
}

Playlist &Playlist::operator=(const Playlist &data)
{
    beginResetModel();
    name = data.name;
    current = data.current;
    container = data.container;
    endResetModel();
    return *this;
}

QString Playlist::getName() const
{
    return name;
}

Playlist& Playlist::operator=(Playlist &&data)
{
    data.beginResetModel();
    beginResetModel();
    current = data.current;
    data.current = 0;
    name = std::move(data.name);
    container = std::move(data.container);
    endResetModel();
    data.endResetModel();
    return *this;
}

int Playlist::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return 0;
    }
    return container.size();
}

QVariant Playlist::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
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
        return QPixmap(":/images/playlist/song.png");
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue<Song>(target);
    }
    case PlaylistRole::PlayingRole:
    {
        return index.row() == this->current;
    }
    case PlaylistRole::ArtistRole:
    {
        return target.getArtist();
    }
    case Qt::ToolTipRole:
    {
        return QString("By %1").arg(target.getArtist());
    }
    default:
    {
        return {};
    }
    }
}

void Playlist::insertSong(int row, const Song &target)
{
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, target);
    endInsertRows();
    emit songsChanged();
}

void Playlist::insertSong(int row, const SongList &target)
{
    beginInsertRows(QModelIndex(), row, row + target.size());
    for(const Song &element : target)
    {
        container.insert(row, element);
    }
    endInsertRows();
    emit songsChanged();
}

void Playlist::appendSong(const Song &target)
{
    insertSong(container.size(), target);
}

void Playlist::appendSong(const SongList &target)
{
    insertSong(container.size(), target);
}

void Playlist::prependSong(const Song &target)
{
    insertSong(0, target);
}

void Playlist::prependSong(const SongList &target)
{
    insertSong(0, target);
}

void Playlist::removeSong(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    container.remove(row);
    emit songsChanged();
    endRemoveRows();
}

void Playlist::setName(const QString &name)
{
    this->name = name;
    emit nameChanged(name);
}

void Playlist::setCurrentSong(qint64 value)
{
    int temp = current;
    current = value;

    emit dataChanged(index(current), index(current), {PlaylistRole::PlayingRole});
    emit dataChanged(index(temp), index(temp), {PlaylistRole::PlayingRole});
    emit currentSongChanged(current);
}

const SongList &Playlist::songs() const
{
    return container;
}

qint64 Playlist::getCurrentSong() const
{
    return current;
}

bool operator==(const Playlist &one, const Playlist &two)
{
    if(one.name != two.name)
    {
        return false;
    }
    else if(one.container != two.container)
    {
        return false;
    }
    else
    {
        return true;
    }
}
bool operator!=(const Playlist &one, const Playlist &two)
{
    return !(one == two);
}

QDataStream& operator>>(QDataStream &stream, Playlist &data)
{
    stream >> data.name;
    stream >> data.current;

    data.beginResetModel();
    stream >> data.container;
    data.endResetModel();

    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Playlist &data)
{
    stream << data.name;
    stream << data.current;
    stream << data.container;
    return stream;
}
