#include "include/dialogs/playlistplayer.h"
#include "include/models/playlistmodel.h"
#include "include/dialogs/artistview.h"
#include "ui_artistview.h"

void ArtistView::updateMetaData()
{
    if(mainModel != nullptr)
    {
        Artist artist = mainModel->artist();
        ui->nameLabel->setText(artist.getName());
        ui->biographyBrowser->setText(artist.getBiography());
        ui->photoView->setImage(artist.getPhoto().toImage());
        setWindowTitle(QString("%1 - Artist Page").arg(artist.getName()));
    }
}

void ArtistView::playPlaylist(const QModelIndex &index)
{
    if(index.isValid())
    {
        const Playlist &value = index.data(Qt::UserRole).value<Playlist>();
        std::unique_ptr<PlaylistModel> target = std::make_unique<PlaylistModel>(value);
        PlaylistPlayer player;
        player.setModel(target.get());
        player.exec();
    }
}

void ArtistView::updateModel()
{
    if(mainModel != nullptr)
    {
        updateMetaData();
        ui->playlistView->setModel(mainModel);
    }
}

ArtistView::ArtistView(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::ArtistView>();
    ui->setupUi(this);
}

ArtistView::~ArtistView()
{}

ArtistModel *ArtistView::model()
{
    return mainModel;
}

void ArtistView::setModel(ArtistModel* value)
{
    mainModel = value;
    updateModel();
}
