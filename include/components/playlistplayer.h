#ifndef PLAYLISTPLAYER_H
#define PLAYLISTPLAYER_H

#include <QWidget>
#include "include/components/player.h"
#include "include/models/proxyplaylistmodel.h"

namespace Ui { class PlaylistPlayer; }

class PlaylistPlayer : public QWidget
{
    Q_OBJECT
private slots:
    void updateModel();
    void updateCurrentTrack();
    void playSong(const QModelIndex &index);

public:
    explicit PlaylistPlayer(QWidget *parent = nullptr);
    ~PlaylistPlayer();

    Player* player();
    const Player* player() const;

    std::shared_ptr<ProxyPlaylistModel> model();
    void setModel(std::shared_ptr<ProxyPlaylistModel> &model);

private:
    std::unique_ptr<Ui::PlaylistPlayer> ui;
    std::shared_ptr<ProxyPlaylistModel> _model;
};

#endif // PLAYLISTPLAYER_H
