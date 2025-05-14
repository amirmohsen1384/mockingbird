#include "include/components/player.h"
#include <QMediaDevices>
#include <QAudioOutput>
#include <QAudioDevice>
#include "ui_player.h"
#include <QFileInfo>
#include <QTime>

Player::Player(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::Player;
    ui->setupUi(this);

    player = std::make_unique<QMediaPlayer>();
    output = std::make_unique<QAudioOutput>();

    player->setAudioOutput(output.get());
    output->setDevice(QMediaDevices::defaultAudioOutput());

    connect(this, &Player::shuffleModeChanged, this, &Player::updateShuffleButton);
    connect(this, &Player::infiniteModeChanged, this, &Player::updateInfiniteButton);
    connect(player.get(), &QMediaPlayer::sourceChanged, this, &Player::updateMetaData);
    connect(player.get(), &QMediaPlayer::playingChanged, this, &Player::updatePlayback);
    connect(player.get(), &QMediaPlayer::positionChanged, this, &Player::updateProgress);
    connect(ui->shuffleButton, &QPushButton::toggled, this, &Player::shuffleModeChanged);
    connect(player.get(), &QMediaPlayer::seekableChanged, this, &Player::updateSeekingControl);
    connect(ui->progressSlider, &QSlider::sliderMoved, player.get(), &QMediaPlayer::setPosition);
    connect(player.get(), &QMediaPlayer::playbackRateChanged, this, &Player::updatePlaybackSpeed);
    connect(ui->progressSlider, &QSlider::sliderPressed, [&]() { player->setPosition(ui->progressSlider->value()); });
}

Player::~Player()
{
    player->stop();
    delete ui;
}

QUrl Player::source() const
{
    return player->source();
}

bool Player::isPlaying() const
{
    return player->isPlaying();
}

bool Player::isShuffleMode() const
{
    return ui->shuffleButton->isChecked();
}

bool Player::isInfiniteMode() const
{
    return player->loops() == QMediaPlayer::Infinite ? true : false;
}

void Player::updateMetaData()
{
    QFileInfo info(player->source().toLocalFile());
    this->setWindowTitle(info.baseName());
}

void Player::updateProgress()
{
    if(player->duration() == player->position() && !isInfiniteMode())
    {
        player->stop();
        emit sourceFinished();
    }

    const quint64 total = player->duration() / 1000;
    const quint64 progress = player->position() / 1000;

    ui->progressSlider->setMinimum(0);
    ui->progressSlider->setMaximum(player->duration());

    ui->progressSlider->setValue(player->position());
    QTime elapsedTime(progress / 3600, (progress / 60) % 60, progress % 60);
    ui->elapsedTimeLabel->setText(elapsedTime.toString(elapsedTime.hour() > 0 ? "hh:mm:ss" : "mm:ss"));

    QTime totalTime(total / 3600, (total / 60) % 60, total % 60);
    ui->totalTimeLabel->setText(totalTime.toString(totalTime.hour() > 0 ? "hh:mm:ss" : "mm:ss"));
}

void Player::updatePlayback()
{
    if(player->isPlaying())
    {
        ui->playbackButton->setToolTip("Pause");
        ui->playbackButton->setIcon(QIcon(":/images/player/pause.png"));
    }
    else
    {
        ui->playbackButton->setToolTip("Play");
        ui->playbackButton->setIcon(QIcon(":/images/player/play.png"));
    }
}

void Player::updateShuffleButton()
{
    ui->shuffleButton->setToolTip(isShuffleMode() ? "Sequential" : "Shuffle");
    ui->shuffleButton->setIcon(QIcon(QString(":/images/player/%1.png").arg(isShuffleMode() ? "no-shuffle" : "shuffle")));
}

void Player::updatePlaybackSpeed()
{
    ui->speedButton->setText(QString::number(player->playbackRate(), '0', 2));
}

void Player::updateSeekingControl()
{
    bool state = player->isSeekable();
    ui->stopButton->setEnabled(state);
    ui->speedButton->setEnabled(state);
    ui->replayButton->setEnabled(state);
    ui->forwardButton->setEnabled(state);
    ui->progressSlider->setEnabled(state);
    ui->playbackButton->setEnabled(state);
    ui->totalTimeLabel->setEnabled(state);
    ui->elapsedTimeLabel->setEnabled(state);
}

void Player::updateInfiniteButton()
{
    ui->repeatButton->setToolTip(isInfiniteMode() ? "Once" : "Infinite");
    ui->repeatButton->setIcon(QIcon(QString(":/images/player/%1.png").arg(isInfiniteMode() ? "no-repeat" : "repeat")));
}

void Player::setSource(const QUrl &source)
{
    player->stop();
    player->setSource(source);
    if(player->error() == QMediaPlayer::NoError) {
        player->play();
    }
}

void Player::stop()
{
    player->stop();
}

void Player::replay()
{
    if(player->isSeekable()) {
        player->setPosition(player->position() - 10 * std::pow(10, 3));
    }

}

void Player::forward()
{
    if(player->isSeekable()) {
        player->setPosition(player->position() + 10 * std::pow(10, 3));
    }
}

void Player::controlPlaybackSpeed()
{
    player->setPlaybackRate(std::max(std::fmod(player->playbackRate() + 0.25, 2.25), 0.25));
}

void Player::setShuffleMode(bool value)
{
    ui->shuffleButton->setChecked(value);
    emit shuffleModeChanged(value);
}

void Player::setInfiniteMode(bool value)
{
    player->setLoops(value ? QMediaPlayer::Infinite : QMediaPlayer::Once);
    emit infiniteModeChanged(value);
}

void Player::controlPlayback()
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
