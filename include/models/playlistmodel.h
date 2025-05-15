#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include "playlist.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlaylistModel(QObject *parent = nullptr);
    PlaylistModel(PlaylistModel &&data, QObject *parent = nullptr);
    PlaylistModel(const PlaylistModel &data, QObject *parent = nullptr);

    PlaylistModel& operator=(const PlaylistModel &data);
    PlaylistModel& operator=(PlaylistModel &&data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    PlaylistList& container();
    const PlaylistList& container() const;

public slots:
    void insertPlaylist(int row, const Playlist &target);
    void insertPlaylist(int row, const PlaylistList &target);

    void prependPlaylist(const Playlist &target);
    void prependPlaylist(const PlaylistList &target);

    void appendPlaylist(const Playlist &target);
    void appendPlaylist(const PlaylistList &target);

    void removePlaylist(int row);
    Playlist takePlaylist(int row);

signals:
    void playlistsChanged();

private:
    PlaylistList container;
};

#endif // PLAYLISTMODEL_H
