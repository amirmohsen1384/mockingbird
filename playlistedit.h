#ifndef PLAYLISTEDIT_H
#define PLAYLISTEDIT_H

#include <QWidget>
#include <QItemSelectionModel>
#include "include/models/playlistmodel.h"

namespace Ui
{
    class PlaylistEdit;
}

class PlaylistEdit : public QWidget
{
    Q_OBJECT
private slots:
    void updateModel();
    void connectComponents();

public:
    explicit PlaylistEdit(QWidget *parent = nullptr);
    ~PlaylistEdit();

    std::shared_ptr<PlaylistModel> model();
    void setModel(std::shared_ptr<PlaylistModel> value);

public slots:
    void addSong();
    void removeSong();
    void editSong(const QModelIndex &index);

private:
    QItemSelectionModel *selectionModel;
    std::unique_ptr<Ui::PlaylistEdit> ui;
    std::shared_ptr<PlaylistModel> mainModel;
};

#endif // PLAYLISTEDIT_H
