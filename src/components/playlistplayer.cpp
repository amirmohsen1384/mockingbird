#include "include/components/playlistplayer.h"
#include "ui_playlistplayer.h"

PlaylistPlayer::PlaylistPlayer(QWidget *parent) : QWidget(parent), ui(new Ui::PlaylistPlayer)
{
    ui->setupUi(this);
    ui->playlistView->setModel(&songs);
    ui->player->setSource(QUrl::fromLocalFile("C:/Users/Amir Mohsen/Downloads/Music/when_im_gone.mp3"));
}

PlaylistPlayer::~PlaylistPlayer()
{
    delete ui;
}

Playlist &PlaylistPlayer::playlist()
{
    return songs;
}

const Playlist &PlaylistPlayer::playlist() const
{
    return songs;
}
