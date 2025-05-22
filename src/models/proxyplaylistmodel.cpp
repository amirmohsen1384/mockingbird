#include "include/models/proxyplaylistmodel.h"

ProxyPlaylistModel::ProxyPlaylistModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    connect(this, &ProxyPlaylistModel::sortRoleChanged, this, &ProxyPlaylistModel::arrange);
}

int ProxyPlaylistModel::getMinimumYear() const
{
    return minYear;
}

void ProxyPlaylistModel::setMinimumYear(int value)
{
    minYear = value;
    invalidateFilter();
}

int ProxyPlaylistModel::getMaximumYear() const
{
    return maxYear;
}

bool ProxyPlaylistModel::getGenreFilteringEnabled() const
{
    return filteringGenre;
}

Qt::SortOrder ProxyPlaylistModel::getSortOrder() const
{
    return order;
}

void ProxyPlaylistModel::setMaximumYear(int value)
{
    maxYear = value;
    invalidateFilter();
}

void ProxyPlaylistModel::setGenreFilteringEnabled(bool value)
{
    filteringGenre = value;
    invalidateFilter();
}

void ProxyPlaylistModel::setSortOrder(Qt::SortOrder order)
{
    this->order = order;
    arrange();
}

Song::Genre ProxyPlaylistModel::getFilteringGenre() const
{
    return genre;
}

bool ProxyPlaylistModel::acceptsWith(const QModelIndex &index) const
{
    if(filteringGenre)
    {
        Song::Genre target = index.data(Playlist::GenreRole).value<Song::Genre>();
        if(genre != target)
        {
            return false;
        }
    }
    int year = index.data(Playlist::YearRole).toInt();
    return year >= minYear && year <= maxYear;
}

void ProxyPlaylistModel::arrange()
{
    this->sort(0, getSortOrder());
}

void ProxyPlaylistModel::setFilteringGenre(Song::Genre genre)
{
    this->genre = genre;
    invalidateFilter();
}

bool ProxyPlaylistModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex &index = sourceModel()->index(source_row, 0, source_parent);
    const QString &name = index.data(Qt::DisplayRole).toString();
    return acceptsWith(index) && name.contains(filterRegularExpression());
}
