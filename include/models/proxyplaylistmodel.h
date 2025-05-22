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
    bool getGenreFilteringEnabled() const;
    Song::Genre getFilteringGenre() const;

    bool acceptsWith(const QModelIndex &index) const;

public slots:
    void arrange();

    void setMinimumYear(int value);
    void setMaximumYear(int value);
    void setSortOrder(Qt::SortOrder order);
    void setGenreFilteringEnabled(bool value);
    void setFilteringGenre(Song::Genre genre);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    Qt::SortOrder order;
    int minYear = _min_year;
    bool filteringGenre = true;
    Song::Genre genre = Song::Genre::Classic;
    int maxYear = QDate::currentDate().year();
};

#endif // PROXYPLAYLISTMODEL_H
