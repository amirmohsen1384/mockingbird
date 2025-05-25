#include "include/models/artistgroupmodel.h"
#include "include/core/artist.h"

void ArtistGroupModel::updateModel()
{
    beginResetModel();

    QDir artists = Storage::songs();
    auto names = artists.entryList({"*"}, QDir::AllDirs | QDir::NoDotAndDotDot);
    for(const QString &value : names)
    {
    }

    endResetModel();
}

ArtistGroupModel::ArtistGroupModel(QObject *parent) : QAbstractListModel(parent)
{
    watcher.addPath(Storage::songs().absolutePath());
    connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &ArtistGroupModel::updateModel);
}

int ArtistGroupModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ArtistGroupModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
