#include "include/components/playlistplayer.h"
#include "ui_playlistplayer.h"

void PlaylistPlayer::updateModel()
{
    ui->player->setModel(_model);
    ui->playlistView->setModel(_model.get());
    _model->setData(QModelIndex(), Playlist::PlayingRole, ui->player->getCurrentTrack());
}

PlaylistPlayer::PlaylistPlayer(QWidget *parent) : QWidget(parent), ui(new Ui::PlaylistPlayer)
{
    ui->setupUi(this);
}

PlaylistPlayer::~PlaylistPlayer() {}

void PlaylistPlayer::setModel(std::shared_ptr<ProxyPlaylistModel> &model)
{
    this->_model = model;
    updateModel();
}

std::shared_ptr<ProxyPlaylistModel> PlaylistPlayer::model()
{
    return _model;
}
