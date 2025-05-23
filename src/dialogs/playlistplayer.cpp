#include "include/dialogs/playlistplayer.h"
#include "ui_playlistplayer.h"

void PlaylistPlayer::updateModel()
{
    ui->player->setModel(_model);
    ui->player->setCurrentTrack(0);
    ui->playlistView->setModel(_model);
    _model->setData(QModelIndex(), Playlist::PlayingRole, ui->player->getCurrentTrack());
}

void PlaylistPlayer::updateCurrentTrack()
{
    QModelIndex index  = _model->index(ui->player->getCurrentTrack(), 0);
    _model->setData(QModelIndex(), Playlist::PlayingRole, ui->player->getCurrentTrack());
    setWindowTitle(QString("%1 - Media Player").arg(index.data(Qt::DisplayRole).toString()));
}

void PlaylistPlayer::playSong(const QModelIndex &index)
{
    ui->player->setCurrentTrack(index.row());
}

PlaylistPlayer::PlaylistPlayer(QWidget *parent) : QDialog(parent), ui(new Ui::PlaylistPlayer)
{
    ui->setupUi(this);
    connect(ui->player, &Player::currentTrackChanged, this, &PlaylistPlayer::updateCurrentTrack);
}

void PlaylistPlayer::setModel(QAbstractItemModel *model)
{
    this->_model = model;
    updateModel();
}

QAbstractItemModel *PlaylistPlayer::model()
{
    return _model;
}

PlaylistPlayer::~PlaylistPlayer() {}
