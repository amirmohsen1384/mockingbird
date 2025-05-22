#include "include/components/playlistplayer.h"
#include "ui_playlistplayer.h"

void PlaylistPlayer::updateModel()
{
    ui->player->setModel(_model);
    ui->playlistView->setModel(_model.get());
    _model->sourceModel()->setData(QModelIndex(), Playlist::PlayingRole, ui->player->getCurrentTrack());
}

void PlaylistPlayer::updateCurrentTrack()
{
    _model->sourceModel()->setData(QModelIndex(), Playlist::PlayingRole, ui->player->getCurrentTrack());
}

void PlaylistPlayer::playSong(const QModelIndex &index)
{
    ui->player->setCurrentTrack(index.row());
}

PlaylistPlayer::PlaylistPlayer(QWidget *parent) : QWidget(parent), ui(new Ui::PlaylistPlayer)
{
    ui->setupUi(this);
    connect(ui->player, &Player::currentTrackChanged, this, &PlaylistPlayer::updateCurrentTrack);
}

PlaylistPlayer::~PlaylistPlayer() {}

Player *PlaylistPlayer::player()
{
    return ui->player;
}

const Player *PlaylistPlayer::player() const
{
    return ui->player;
}

void PlaylistPlayer::setModel(std::shared_ptr<ProxyPlaylistModel> &model)
{
    this->_model = model;
    updateModel();
}

std::shared_ptr<ProxyPlaylistModel> PlaylistPlayer::model()
{
    return _model;
}
