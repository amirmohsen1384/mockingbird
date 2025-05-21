#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H

#include <QWidget>
#include "include/models/proxyplaylistmodel.h"

namespace Ui { class PlaylistPlayer; }

class PlaylistPlayer : public QWidget
{
    Q_OBJECT
private slots:
    void updateModel();
    void updateCurrentTrack();

public:
    explicit PlaylistPlayer(QWidget *parent = nullptr);
    ~PlaylistPlayer();

    std::shared_ptr<ProxyPlaylistModel> model();
    void setModel(std::shared_ptr<ProxyPlaylistModel> &model);

private:
    std::unique_ptr<Ui::PlaylistPlayer> ui;
    std::shared_ptr<ProxyPlaylistModel> _model;
};

#endif // PLAYLISTPLAYER_H
