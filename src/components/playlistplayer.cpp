#include "include/components/playlistplayer.h"
#include "ui_playlistplayer.h"
#include <QRandomGenerator64>

void PlaylistPlayer::playSong(const QModelIndex &index)
{
    container.setCurrentSong(index.row());
}

void PlaylistPlayer::navigatePlaylist()
{
    int index = 0;
    const SongList &songs = container.songs();
    if(!ui->player->isShuffleMode())
    {
        index = (container.getCurrentSong() + 1) % songs.size();
    }
    else
    {
        index = QRandomGenerator64::global()->bounded(0, songs.size());
    }
    container.setCurrentSong(index);
}

void PlaylistPlayer::updatePlayer()
{
    ui->player->stop();
    int index = container.getCurrentSong();
    if(!container.songs().isEmpty() && index >= 0 && index < container.songs().size())
    {
        const Song &target = container.songs().at(index);
        ui->player->setSource(target.getAddress());
    }
}

PlaylistPlayer::PlaylistPlayer(QWidget *parent) : QWidget(parent), ui(new Ui::PlaylistPlayer)
{
    ui->setupUi(this);
    ui->playlistView->setModel(&container);
    connect(&container, &Playlist::nameChanged, ui->nameLabel, &QLabel::setText);
    connect(&container, &Playlist::songsChanged, this, &PlaylistPlayer::updatePlayer);
    connect(&container, &Playlist::nameChanged, this, &PlaylistPlayer::setWindowTitle);
    connect(ui->player, &Player::sourceFinished, this, &PlaylistPlayer::navigatePlaylist);
    connect(&container, &Playlist::currentSongChanged, this, &PlaylistPlayer::updatePlayer);
}

PlaylistPlayer::~PlaylistPlayer()
{
    delete ui;
}

Playlist &PlaylistPlayer::playlist()
{
    return container;
}

const Playlist &PlaylistPlayer::playlist() const
{
    return container;
}
