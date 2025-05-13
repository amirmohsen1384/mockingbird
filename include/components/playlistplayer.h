#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H

#include <QWidget>
#include "include/core/playlist.h"

namespace Ui { class PlaylistPlayer; }

class PlaylistPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistPlayer(QWidget *parent = nullptr);
    ~PlaylistPlayer();

    const Playlist& playlist() const;
    Playlist& playlist();

private:
    Playlist songs;
    Ui::PlaylistPlayer *ui;
};

#endif // PLAYLISTPLAYER_H
