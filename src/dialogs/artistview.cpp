#include "include/dialogs/artistview.h"
#include "include/models/playlistmodel.h"
#include "include/dialogs/playlistplayer.h"
#include "ui_artistview.h"

void ArtistView::updateMetaData()
{
    if(mainModel.get() != nullptr)
    {
        const Artist &artist = mainModel->artist();
        ui->nameLabel->setText(artist.getName());
        ui->biographyLabel->setText(artist.getBiography());
        ui->photoView->setImage(artist.getPhoto().toImage());
    }
}

void ArtistView::playPlaylist(const QModelIndex &index)
{
    if(!index.isValid())
    {
        return;
    }
    const Playlist &value = index.data(Qt::UserRole).value<Playlist>();
    std::unique_ptr<PlaylistModel> target = std::make_unique<PlaylistModel>(value);
    PlaylistPlayer player;
    player.setModel(target.get());
    player.exec();
}

void ArtistView::updateModel()
{
    if(mainModel.get() != nullptr)
    {
        updateMetaData();
        ui->playlistView->setModel(mainModel.get());
    }
}

ArtistView::ArtistView(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::ArtistView>();
    ui->setupUi(this);
}

ArtistView::~ArtistView() {}

std::shared_ptr<ArtistModel> ArtistView::model()
{
    return mainModel;
}

void ArtistView::setModel(std::shared_ptr<ArtistModel> value)
{
    mainModel = value;
    updateModel();
}
