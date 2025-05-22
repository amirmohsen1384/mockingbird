#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include <QWidget>
#include <QDialog>
#include "include/components/playlistplayer.h"
#include "include/models/proxyplaylistmodel.h"
#include "include/components/custom/filteredit.h"

namespace Ui
{
    class PlaylistView;
}

class PlaylistView : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistView(QWidget *parent = nullptr);
    ~PlaylistView();

    std::shared_ptr<ProxyPlaylistModel> getModel();
    void setModel(std::shared_ptr<ProxyPlaylistModel> model);

public slots:
    void showArrangePanel(bool toggle);
    void showFilterEdit(bool toggle);
    void showFindPanel(bool toggle);
    void playSong();

private slots:
    void updateArrangeCriteria();
    void updateFindCriteria();
    void updateFilter();
    void updateModel();

private:
    std::unique_ptr<Ui::PlaylistView> ui;
    std::shared_ptr<ProxyPlaylistModel> model;
};

#endif // PLAYLISTVIEW_H
