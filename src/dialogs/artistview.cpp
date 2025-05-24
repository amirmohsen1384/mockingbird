#include "include/dialogs/playlistplayer.h"
#include "include/models/playlistmodel.h"
#include "include/dialogs/artistview.h"
#include "ui_artistview.h"

void ArtistView::updateMetaData()
{
    Artist artist = mainModel->artist();
    ui->nameLabel->setText(artist.getName());
    ui->biographyBrowser->setText(artist.getBiography());
    ui->photoView->setImage(artist.getPhoto().toImage());
    setWindowTitle(QString("%1 - Artist Page").arg(artist.getName()));
}

void ArtistView::playPlaylist(const QModelIndex &index)
{
    if(index.isValid())
    {
        const Playlist &value = index.data(Qt::UserRole).value<Playlist>();
        PlaylistPlayer player(value);
        player.exec();
    }
}

ArtistView::ArtistView(const Artist &value, QWidget *parent) : ArtistView(parent)
{
    setArtist(value);
}

ArtistView::ArtistView(QWidget *parent) : QDialog(parent)
{
    ui = std::make_unique<Ui::ArtistView>();
    ui->setupUi(this);

    mainModel = std::make_unique<ArtistModel>();
    ui->playlistView->setModel(mainModel.get());
}

ArtistView::~ArtistView()
{}

Artist ArtistView::artist() const
{
    return mainModel->artist();
}

void ArtistView::setArtist(const Artist &value)
{
    mainModel->setArtist(value);
    updateMetaData();
}
