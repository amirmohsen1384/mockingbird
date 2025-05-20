#include "include/models/proxyplaylistmodel.h"

ProxyPlaylistModel::ProxyPlaylistModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    connect(this, &ProxyPlaylistModel::sortOrderChanged, this, [&](Qt::SortOrder value)
    {
        this->sort(0, value);
    }
    );
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

Qt::SortOrder ProxyPlaylistModel::getSortOrder() const
{
    return order;
}

void ProxyPlaylistModel::setMaximumYear(int value)
{
    maxYear = value;
    invalidateFilter();
}

void ProxyPlaylistModel::setSortOrder(Qt::SortOrder order)
{
    this->order = order;
    emit sortOrderChanged(order);
}

Song::Genre ProxyPlaylistModel::getFilteringGenre() const
{
    return genre;
}

bool ProxyPlaylistModel::acceptsWith(const QModelIndex &index) const
{
    if(genre != Song::Genre::NoGenre)
    {
        Song::Genre target = qvariant_cast<Song::Genre>(index.data(Playlist::GenreRole));
        if(genre != target)
        {
            return false;
        }
    }
    int year = index.data(Playlist::YearRole).toInt();
    return year >= minYear && year <= maxYear;
}

void ProxyPlaylistModel::setFilteringGenre(Song::Genre genre)
{
    this->genre = genre;
    invalidateFilter();
}

bool ProxyPlaylistModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex &index = sourceModel()->index(source_row, 0, source_parent);
    return acceptsWith(index) && QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}
