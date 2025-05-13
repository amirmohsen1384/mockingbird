#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QAbstractListModel>
#include "include/core/song.h"

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

    void replaceSong(int row, const Song &target);

    void setName(const QString &name);

signals:
    void nameChanged(const QString &name);

private:
    QString name;
    SongList container;
};

bool operator==(const Playlist &one, const Playlist &two);
bool operator!=(const Playlist &one, const Playlist &two);

QDataStream& operator>>(QDataStream &stream, Playlist &data);
QDataStream& operator<<(QDataStream &stream, const Playlist &data);

Q_DECLARE_METATYPE(Playlist)

#endif // PLAYLIST_H
