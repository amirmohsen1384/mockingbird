#ifndef ARTISTVIEW_H
#define ARTISTVIEW_H

#include <QDialog>
#include "include/models/artistmodel.h"

namespace Ui {
class ArtistView;
}

class ArtistView : public QDialog
{
    Q_OBJECT
    void updateModel();
    void updateMetaData();

public slots:
    void playPlaylist(const QModelIndex &index);

public:
    explicit ArtistView(QWidget *parent = nullptr);
    ~ArtistView();

    ArtistModel* model();
    void setModel(ArtistModel* value);

private:
    ArtistModel* mainModel = nullptr;
    std::unique_ptr<Ui::ArtistView> ui;
};

#endif // ARTISTVIEW_H
