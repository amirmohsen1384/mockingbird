#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include "include/core/playlist.h"

enum PlaylistRole {PlayingRole = Qt::UserRole + 1, ArtistRole = Qt::UserRole + 2};

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_DISABLE_COPY_MOVE(PlaylistModel)
    PlaylistModel(QObject *parent = nullptr);

    qint64 getCurrentSong() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void insertSong(int row, const Song &target);
    void insertSong(int row, const SongList &target);

    void appendSong(const Song &target);
    void appendSong(const SongList &target);

    void prependSong(const Song &target);
    void prependSong(const SongList &target);

    void removeSong(int row);

    void setName(const QString &name);
    void setCurrentSong(qint64 value);

signals:
    void songsChanged();
    void nameChanged(const QString &name);
    void currentSongChanged(qint64 song);

private:
    qint64 current;
    Playlist container;
};

class SongDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SongDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PLAYLISTMODEL_H
