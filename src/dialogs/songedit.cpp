#include "include/dialogs/songedit.h"
#include <QMediaMetaData>
#include <QMediaDevices>
#include "ui_songedit.h"
#include <QAudioOutput>
#include <QAudioDevice>
#include <QFileDialog>
#include <QMessageBox>
#include <exception>

SongEdit::SongEdit(QWidget *parent) : QDialog{parent}
{
    ui = std::make_unique<Ui::SongEdit>();
    ui->setupUi(this);

    output = std::make_unique<QAudioOutput>();
    output->setDevice(QMediaDevices::defaultAudioOutput());

    player = std::make_unique<QMediaPlayer>();
    player->setAudioOutput(output.get());

    ui->genreEdit->setModel(&model);
    ui->playbackButton->setVisible(false);
    ui->releaseYearEdit->setValue(QDate::currentDate().year());

    connect(this, &SongEdit::locationChanged, player.get(), &QMediaPlayer::setSource);
    connect(player.get(), &QMediaPlayer::sourceChanged, this, &SongEdit::updateSource);
    connect(player.get(), &QMediaPlayer::metaDataChanged, this, &SongEdit::updateMetaData);
    connect(player.get(), &QMediaPlayer::playingChanged, this, &SongEdit::updatePlaybackControl);

    connect(ui->nameEdit, &QLineEdit::textChanged, this, &SongEdit::nameChanged);
    connect(ui->artistEdit, &QLineEdit::textChanged, this, &SongEdit::artistChanged);
    connect(ui->fileNameEdit, &QLineEdit::textChanged, this, [&](const QString &text)
    {
        emit locationChanged(QUrl::fromLocalFile(text));
    }
    );
    connect(ui->genreEdit, &QComboBox::currentIndexChanged, this, [&](int index)
    {
        emit genreChanged(static_cast<Song::Genre>(index));
    }
    );
    connect(ui->coverView, &ImageView::imageChanged, this, [&](const QImage &image)
    {
        emit SongEdit::coverChanged(QPixmap::fromImage(image));
    }
    );
    connect(ui->releaseYearEdit, &QSpinBox::valueChanged, this, &SongEdit::releasedYearChanged);
    ui->releaseYearEdit->setMinimum(_min_year);
}

SongEdit::SongEdit(const Song &value, QWidget *parent) : SongEdit(parent)
{
    setValue(value);
}

QFileDialog *SongEdit::browseFile()
{
    QFileDialog *dialog = new QFileDialog(this);
    dialog->setDirectory(QDir::home());
    dialog->setAcceptMode(QFileDialog::AcceptOpen);
    dialog->setFileMode(QFileDialog::ExistingFile);
    dialog->setWindowTitle("Select a file to open");
    dialog->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    return dialog;
}

void SongEdit::updateSource()
{
    player->stop();
    ui->playbackButton->setVisible(player->mediaStatus() != QMediaPlayer::InvalidMedia);
}

void SongEdit::openSongFile()
{
    static QStringList history;
    std::unique_ptr<QFileDialog> dialog(browseFile());
    dialog->setNameFilter("Songs (*.mp3 *.wav *.aiff *.pcm *.aac *.ogg *.wma *.m4a *.ape *.alac)");
    dialog->setHistory(history);
    if(dialog->exec() == QDialog::Accepted)
    {
        const QString fileName = dialog->selectedFiles().constFirst();
        setLocation(QUrl::fromLocalFile(fileName));
        history.append(fileName);
    }
}

void SongEdit::openImageFile()
{
    static QStringList history;
    std::unique_ptr<QFileDialog> dialog(browseFile());
    dialog->setNameFilter("Pictures (*.bmp *.png *.tiff *.gif *.jpeg *.jpg *.tif)");
    dialog->setHistory(history);
    if(dialog->exec() == QDialog::Accepted)
    {
        const QString fileName = dialog->selectedFiles().constFirst();
        setCover(QPixmap(fileName));
        history.append(fileName);
    }
}

void SongEdit::updateMetaData()
{
    // Fetches the meta data from the media player
    QMediaMetaData data = player->metaData();

    // Initializes the name
    QVariant name = data.value(QMediaMetaData::Title);
    if(name.isNull())
    {
        name = data.value(QMediaMetaData::AlbumTitle);
        if(name.isNull())
        {
            name = data.value(QMediaMetaData::Description);
        }
    }
    if(getName().isEmpty())
    {
        setName(name.toString());
    }

    // Initializes the image cover
    QVariant cover = data.value(QMediaMetaData::ThumbnailImage);
    if(cover.isNull())
    {
        cover = data.value(QMediaMetaData::CoverArtImage);
    }
    if(getCover().isNull())
    {
        setCover(qvariant_cast<QPixmap>(cover));
    }

    // Initializes the artist
    QVariant artist = data.value(QMediaMetaData::AlbumArtist);
    if(artist.isNull())
    {
        artist = data.value(QMediaMetaData::Author);
        if(artist.isNull())
        {
            artist = data.value(QMediaMetaData::ContributingArtist);
        }
    }
    if(getArtist().isEmpty())
    {
        setArtist(artist.toString());
    }
}

void SongEdit::controlPlayback()
{
    if(player->isPlaying())
    {
        player->pause();
    }
    else
    {
        player->play();
    }
}

void SongEdit::updatePlaybackControl(bool value)
{
    ui->playbackButton->setToolTip(value ? "Pause" : "Play");
    ui->playbackButton->setIcon(QIcon(QString(":/images/player/%1.png").arg(value ? "pause" : "play")));
}

SongEdit::~SongEdit() {}

Song::Genre SongEdit::getGenre() const
{
    return static_cast<Song::Genre>(ui->genreEdit->currentIndex());
}

int SongEdit::getReleasedYear() const
{
    return ui->releaseYearEdit->value();
}

QString SongEdit::getArtist() const
{
    return ui->artistEdit->text();
}

QUrl SongEdit::getLocation() const
{
    return QUrl::fromLocalFile(ui->fileNameEdit->text());
}

QPixmap SongEdit::getCover() const
{
    return QPixmap::fromImage(ui->coverView->getImage());
}

QString SongEdit::getName() const
{
    return ui->nameEdit->text();
}

Song SongEdit::getValue() const
{
    Song target;
    target.setName(getName());
    target.setCover(getCover());
    target.setGenre(getGenre());
    target.setArtist(getArtist());
    target.setAddress(getLocation());
    target.setPublicationYear(getReleasedYear());
    return target;
}

void SongEdit::setReleasedYear(int value)
{
    ui->releaseYearEdit->setValue(value);
}

void SongEdit::setValue(const Song &value)
{
    setName(value.name);
    setGenre(value.genre);
    setCover(value.cover);
    setArtist(value.artist);
    setLocation(value.address);
    setReleasedYear(value.publicationYear);
    if(!value.getName().isEmpty())
    {
        setWindowTitle(QString("%1 - Song Editor").arg(value.name));
    }
}

void SongEdit::setGenre(Song::Genre value)
{
    ui->genreEdit->setCurrentIndex(static_cast<int>(value));
}

void SongEdit::setName(const QString &value)
{
    ui->nameEdit->setText(value);
}

void SongEdit::setCover(const QPixmap &value)
{
    ui->coverView->setImage(value.toImage());
}

void SongEdit::setArtist(const QString &value)
{
    ui->artistEdit->setText(value);
}

void SongEdit::setLocation(const QUrl &location)
{
    ui->fileNameEdit->setText(location.toString(QUrl::PreferLocalFile));
}

void SongEdit::removeCover()
{
    ui->coverView->setImage(QImage());
}

void SongEdit::accept()
{
    try
    {
        if(!QFile::exists(ui->fileNameEdit->text()) || !QUrl::fromLocalFile(ui->fileNameEdit->text()).isValid())
        {
            throw std::runtime_error("The file name is not valid or exists.");
        }
        else if(ui->nameEdit->text().isEmpty())
        {
            throw std::runtime_error("You have not entered the name.");
        }
        else if(ui->artistEdit->text().isEmpty())
        {
            throw std::runtime_error("You have not entered the artist.");
        }
        QDialog::accept();
    }
    catch(std::exception &e)
    {
        QMessageBox::critical(this, "Error!", e.what());
        return;
    }
}
