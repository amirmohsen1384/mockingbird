#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include "include/core/playlist.h"

class PlaylistGroupModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(PlaylistGroupModel)

    PlaylistGroupModel(QObject *parent) : QAbstractListModel(parent) {}
    ~PlaylistGroupModel() {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    const PlaylistGroup& playlists() const;
    PlaylistGroup& playlists();

public slots:
    void insertPlaylist(int row, const Playlist &target);
    void insertPlaylist(int row, const PlaylistGroup &target);

    void prependPlaylist(const Playlist &target);
    void prependPlaylist(const PlaylistGroup &target);

    void appendPlaylist(const Playlist &target);
    void appendPlaylist(const PlaylistGroup &target);

    void removePlaylist(int row);

signals:
    void playlistsChanged();

private:
    PlaylistGroup container;
};

#endif // PLAYLISTMODEL_H
