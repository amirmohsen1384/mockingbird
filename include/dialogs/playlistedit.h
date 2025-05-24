#ifndef PLAYLISTEDIT_H
#define PLAYLISTEDIT_H

#include <QDialog>
#include "include/models/proxyplaylistmodel.h"

namespace Ui
{
    class PlaylistEdit;
}

class PlaylistEdit : public QDialog
{
    Q_OBJECT
private slots:
    void updateModel();
    void updateMetaData();

public:
    explicit PlaylistEdit(const Playlist &container, QWidget *parent = nullptr);
    explicit PlaylistEdit(QWidget *parent = nullptr);
    ~PlaylistEdit();

    Playlist playlist() const;
    void setPlaylist(const Playlist &container);

private slots:
    void showArrangePanel(bool toggle);
    void showFilterEdit(bool toggle);
    void showFindPanel(bool toggle);

public slots:
    void addSong();
    void removeSong();
    void editSong(const QModelIndex &index);

    void updateArrangeCriteria();
    void updateFindCriteria();
    void updateFilter();

    virtual void accept() override;

private:
    std::unique_ptr<Ui::PlaylistEdit> ui;
    std::unique_ptr<PlaylistModel> sourceModel;
    std::unique_ptr<ProxyPlaylistModel> mainModel;
};

#endif // PLAYLISTEDIT_H
