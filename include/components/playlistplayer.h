#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H

#include <QWidget>
#include "include/models/playlist.h"

namespace Ui { class PlaylistPlayer; }

class PlaylistPlayer : public QWidget
{
    Q_OBJECT

private slots:
    void playSong(const QModelIndex &index);
    void navigatePlaylist();
    void updatePlayer();

public:
    explicit PlaylistPlayer(QWidget *parent = nullptr);
    ~PlaylistPlayer();

    const Playlist& playlist() const;
    Playlist& playlist();

private:
    Playlist container;
    Ui::PlaylistPlayer *ui;
};

#endif // PLAYLISTPLAYER_H
