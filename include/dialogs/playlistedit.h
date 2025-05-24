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
    void commitMetaData();

public:
    explicit PlaylistEdit(QWidget *parent = nullptr);
    ~PlaylistEdit();

    QAbstractItemModel* model();
    void setModel(QAbstractItemModel* value);

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

private:
    std::unique_ptr<Ui::PlaylistEdit> ui;
    std::unique_ptr<ProxyPlaylistModel> mainModel;
};

#endif // PLAYLISTEDIT_H
