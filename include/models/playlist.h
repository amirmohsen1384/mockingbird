#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include "include/core/song.h"

enum PlaylistRole {PlayingRole = Qt::UserRole + 1, ArtistRole = Qt::UserRole + 2};

class Playlist : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit Playlist(QObject *parent = nullptr);
    Playlist(Playlist &&data, QObject *parent = nullptr);
    Playlist(const Playlist &data, QObject *parent = nullptr);

    Playlist& operator=(Playlist &&data);
    Playlist& operator=(const Playlist &data);

    QString getName() const;
    const SongList& songs() const;
    qint64 getCurrentSong() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    friend bool operator==(const Playlist &one, const Playlist &two);
    friend bool operator!=(const Playlist &one, const Playlist &two);

    friend QDataStream& operator>>(QDataStream &stream, Playlist &data);
    friend QDataStream& operator<<(QDataStream &stream, const Playlist &data);

public slots:
    void insertSong(int row, const Song &target);
    void insertSong(int row, const SongList &target);

    void appendSong(const Song &target);
    void appendSong(const SongList &target);

    void prependSong(const Song &target);
    void prependSong(const SongList &target);

    void removeSong(int row);
    Song takeSong(int row);

    void setName(const QString &name);
    void setCurrentSong(qint64 value);

signals:
    void songsChanged();
    void nameChanged(const QString &name);
    void currentSongChanged(qint64 song);

private:
    QString name;
    qint64 current;
    SongList container;
};

bool operator==(const Playlist &one, const Playlist &two);
bool operator!=(const Playlist &one, const Playlist &two);

QDataStream& operator>>(QDataStream &stream, Playlist &data);
QDataStream& operator<<(QDataStream &stream, const Playlist &data);

Q_DECLARE_METATYPE(Playlist)

using PlaylistList = QList<Playlist>;

class SongDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    SongDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // PLAYLIST_H
