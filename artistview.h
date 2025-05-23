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

    std::shared_ptr<ArtistModel> model();
    void setModel(std::shared_ptr<ArtistModel> value);

private:
    std::shared_ptr<ArtistModel> mainModel;
    std::unique_ptr<Ui::ArtistView> ui;
};

#endif // ARTISTVIEW_H
