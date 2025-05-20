#ifndef PROXYPLAYLISTMODEL_H
#define PROXYPLAYLISTMODEL_H

#include "include/models/playlistmodel.h"
#include <QSortFilterProxyModel>

class ProxyPlaylistModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum Sort
    {
        ByName = Qt::DisplayRole,
        ByArtist = Playlist::ArtistRole,
        ByReleasedYear = Playlist::YearRole,
        ByGenre = Playlist::GenreTextRole
    };

public:
    Q_DISABLE_COPY_MOVE(ProxyPlaylistModel)
    explicit ProxyPlaylistModel(QObject *parent = nullptr);

    int getMinimumYear() const;
    int getMaximumYear() const;
    Qt::SortOrder getSortOrder() const;
    Song::Genre getFilteringGenre() const;

    bool acceptsWith(const QModelIndex &index) const;

public slots:
    void setMinimumYear(int value);
    void setMaximumYear(int value);
    void setSortOrder(Qt::SortOrder order);
    void setFilteringGenre(Song::Genre genre);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

signals:
    void sortOrderChanged(Qt::SortOrder order);

private:
    Qt::SortOrder order;
    int minYear = _min_year;
    Song::Genre genre = Song::Genre::NoGenre;
    int maxYear = QDate::currentDate().year();
};

#endif // PROXYPLAYLISTMODEL_H
