#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include "include/core/playlist.h"

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
    static const QVector<int> roles;
public:
    PlaylistModel(QObject *parent = nullptr) : QAbstractListModel(parent), current(-1) {}
    PlaylistModel(const Playlist &initial, QObject *parent = nullptr);
    Q_DISABLE_COPY_MOVE(PlaylistModel)
    ~PlaylistModel() override {}

    QString name() const;
    QPixmap cover() const;
    qint64 currentTrack() const;

    const Playlist& playlist() const;
    void setPlaylist(const Playlist &value);

    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setName(const QString &name);
    void setCurrentTrack(qint64 value);

    void appendSong(const Song &target);
    void appendSong(const SongList &target);

    void prependSong(const Song &target);
    void prependSong(const SongList &target);

    void insertSong(int row, const Song &target);
    void insertSong(int row, const SongList &target);

    void removeSong(int row);

private:
    qint64 current;
    Playlist container;
};

#endif // PLAYLISTMODEL_H
