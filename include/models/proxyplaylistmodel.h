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
        ByReleasedYear = Playlist::YearRole
    };

public:
    Q_DISABLE_COPY_MOVE(ProxyPlaylistModel)
    explicit ProxyPlaylistModel(QObject *parent = nullptr);

    int getMinimumYear() const;
    int getMaximumYear() const;
    Song::Genre getFilteringGenre() const;

    bool acceptsWith(const QModelIndex &index) const;

public slots:
    void setMinimumYear(int value);
    void setMaximumYear(int value);
    void setFilteringGenre(Song::Genre genre);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    int minYear = _min_year;
    Song::Genre genre = Song::Genre::NoGenre;
    int maxYear = QDate::currentDate().year();
};

#endif // PROXYPLAYLISTMODEL_H
