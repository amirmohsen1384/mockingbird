#include "include/models/playlistmodel.h"
#include "include/models/genremodel.h"
#include "include/core/song.h"
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

void PlaylistModel::updateModel()
{
    beginResetModel();

    // Clears the whole store
    store.clear();

    if(ID::isValid(mainId))
    {
        // Loads the new metadata from the record.
        metadata = Playlist::loadFromRecord(mainId);

        // Loads the keys and associated songs from the records.
        IDs keys = Playlist::loadIDsFromRecord(mainId);
        for(const IDContainer &key : keys)
        {
            Song value = Song::loadFromRecord(key);
            if(!value.isNull())
            {
                store.append({value, key});
            }
        }
    }

    endResetModel();
}

PlaylistModel::PlaylistModel(const IDContainer &value, QObject *parent) : QAbstractListModel(parent)
{
    setID(value);
}

int PlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    return store.size();
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const
{
    if(!ID::isValid(mainId) || !index.isValid())
    {
        return {};
    }

    const Song &target = store.at(index.row()).data;

    switch(role)
    {
    case Qt::DisplayRole:
    {
        return target.getName();
    }
    case Qt::BackgroundRole:
    {
        return index.row() == current ? QColor(230, 250, 120) : QVariant();
    }
    case Qt::FontRole:
    {
        return index.row() == current ? QFont("Segoe UI", 10, QFont::Bold) : QVariant();
    }
    case Qt::DecorationRole:
    {
        QImage image = target.getCover();
        if(image.isNull())
        {
            return QPixmap(":/images/playlist/song.png");
        }
        return image.scaled(_cover_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    case Qt::UserRole:
    {
        return QVariant::fromValue<Song>(target);
    }
    case Playlist::PlayingRole:
    {
        return index.row() == current;
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
    case Playlist::KeyRole:
    {
        return store[index.row()].key;
    }
    case Playlist::InfoRole:
    {
        return QVariant::fromValue(store.at(index.row()));
    }
    default:
    {
        return {};
    }
    }
}

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    if(section != 0)
    {
        return {};
    }
    switch(role)
    {
    case Qt::DisplayRole:
    {
        return metadata.getName();
    }
    case Playlist::KeyRole:
    {
        return mainId;
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

bool PlaylistModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if(section != 0)
    {
        return false;
    }
    switch(role)
    {
    case Qt::DisplayRole:
    {
        metadata.setName(value.toString());
        break;
    }
    case Playlist::PlayingRole:
    {
        current = value.toInt();
        break;
    }
    default:
    {
        return false;
    }
    }
    emit headerDataChanged(orientation, 0, 0);
    return true;
}

void PlaylistModel::insertSong(const SongInfo &info)
{
    if(!ID::isValid(info.key))
    {
        qDebug() << "Invalid key. Failed to insert.";
        return;
    }
    auto it = std::lower_bound
    (
        store.cbegin(),
        store.cend(),
        info,
        [&](const SongInfo &one, const SongInfo &two)
        {
            return one.key < two.key;
        }
    );
    int index = std::distance(store.cbegin(), it);
    beginInsertRows(QModelIndex(), index, index);
    store.insert(index, info);
    endInsertRows();
}

void PlaylistModel::removeSong(const IDContainer &value)
{
    if(!ID::isValid(mainId))
    {
        return;
    }
    SongInfo target;
    target.key = value;
    auto result = std::lower_bound
        (
        store.cbegin(),
        store.cend(),
        target,
        [&](const SongInfo &one, const SongInfo &two)
        {
            return one.key < two.key;
        }
    );
    if(result != store.cend() && result->key == value)
    {
        int row = std::distance(store.cbegin(), result);
        beginRemoveRows(QModelIndex(), row, row);
        store.remove(row);
        endRemoveRows();
    }
}

void PlaylistModel::removeSong(int row)
{
    if(!ID::isValid(mainId))
    {
        return;
    }
    beginRemoveRows(QModelIndex(), row, row);
    store.remove(row);
    endRemoveRows();
}

QModelIndex PlaylistModel::fromKey(const IDContainer &value) const
{
    IDs keys = getKeys();
    auto it = std::lower_bound(keys.cbegin(), keys.cend(), value);
    if(*it == value && it != keys.cend())
    {
        return index(std::distance(keys.cbegin(), it));
    }
    else
    {
        return QModelIndex();
    }
}

bool PlaylistModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!ID::isValid(mainId) || !index.isValid())
    {
        return false;
    }

    Song &target = store[index.row()].data;

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
        target.setCover(value.value<QImage>());
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
        target = qvariant_cast<Song>(value);
        emit dataChanged(index, index, roles);
        return true;
    }
    case Playlist::KeyRole:
    {
        store[index.row()].key = value.value<IDContainer>();
        store[index.row()].data = Song::loadFromRecord(store[index.row()].key);
        emit dataChanged(index, index, roles);
        return true;
    }
    default:
    {
        return false;
    }
    }
}

IDContainer PlaylistModel::getID() const
{
    return mainId;
}

void PlaylistModel::setID(const IDContainer &value)
{
    mainId = value;
    updateModel();
}

int PlaylistModel::getCurrentTrack() const
{
    return current;
}

void PlaylistModel::setCurrentTrack(int index)
{
    setData(QModelIndex(), qBound(0, index, rowCount()), Playlist::PlayingRole);
}

void PlaylistModel::saveToRecord() const
{
    metadata.saveToRecord(mainId);
    Playlist::saveIDsToRecord(getKeys(), mainId);
}

IDs PlaylistModel::getKeys() const
{
    IDs container;
    for(const SongInfo &info : store)
    {
        container.append(info.key);
    }
    return container;
}

SongList PlaylistModel::getSongs() const
{
    SongList container;
    for(const SongInfo &info : store)
    {
        container.append(info.data);
    }
    return container;
}

const QList<SongInfo> &PlaylistModel::getStore() const
{
    return store;
}

std::shared_ptr<PlaylistModel> PlaylistModel::clone() const
{
    std::shared_ptr<PlaylistModel> model = std::make_shared<PlaylistModel>();
    for(const SongInfo &song : store)
    {
        model->store.append(song);
    }
    model->metadata = metadata;
    model->current = current;
    model->mainId = mainId;
    return model;
}
