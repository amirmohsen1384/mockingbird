#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include "include/core/playlist.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    PlaylistModel(QObject *parent = nullptr) : QAbstractListModel(parent) {}
    Q_DISABLE_COPY_MOVE(PlaylistModel)
    ~PlaylistModel() override {}

    QString getName() const;
    QPixmap getCover() const;
    const Playlist& getPlaylist() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void removeSong(int row);

    void setName(const QString &name);
    void setCover(const QPixmap &value);

    void appendSong(const Song &target);
    void appendSong(const SongList &target);

    void prependSong(const Song &target);
    void prependSong(const SongList &target);

    void insertSong(int row, const Song &target);
    void insertSong(int row, const SongList &target);

signals:
    void songsChanged();
    void nameChanged(const QString &name);
    void coverChanged(const QPixmap &value);

private:
    Playlist container;
};

#endif // PLAYLISTMODEL_H
