#include "include/core/playlist.h"
#include <QPixmap>

Playlist::Playlist(QObject *parent) : QAbstractListModel(parent)
{}

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
    name = data.name;
    container = data.container;
    return *this;
}

Playlist& Playlist::operator=(Playlist &&data)
{
    name = std::move(data.name);
    container = std::move(data.container);
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

    switch(role) {
    case Qt::DisplayRole: {
        return target.getName();
    }
    case Qt::DecorationRole: {
        return QPixmap(":/images/playlist/song.png");
    }
    case Qt::UserRole: {
        return QVariant::fromValue<Song>(target);
    }
    default: {
        return {};
    }
    }
}

void Playlist::insertSong(int row, const Song &target)
{
    beginInsertRows(QModelIndex(), row, row);
    container.insert(row, target);
    endInsertRows();
}

void Playlist::insertSong(int row, const SongList &target)
{
    beginInsertRows(QModelIndex(), row, row + target.size());
    for(const Song &element : target)
    {
        container.insert(row, element);
    }
    endInsertRows();
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

Song Playlist::takeSong(int row)
{
    Song song = container.at(row);
    removeSong(row);
    return song;
}

void Playlist::replaceSong(int row, const Song &target)
{
    if(row >= 0 && row < container.size()) {
        container.replace(row, target);
        emit dataChanged(index(1), index(1), {Qt::UserRole, Qt::DisplayRole});
    }
}

void Playlist::removeSong(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    container.remove(row);
    endRemoveRows();
}

void Playlist::setName(const QString &name)
{
    this->name = name;
    emit nameChanged(name);
}

const SongList &Playlist::songs() const
{
    return container;
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

    data.beginResetModel();
    stream >> data.container;
    data.endResetModel();

    return stream;
}

QDataStream& operator<<(QDataStream &stream, const Playlist &data)
{
    stream << data.name;
    stream << data.container;
    return stream;
}
