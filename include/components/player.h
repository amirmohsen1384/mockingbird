#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "include/models/playlist.h"

namespace Ui
{
    class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(Player)
    explicit Player(QWidget *parent = nullptr);
    ~Player();
    
    Playlist& playlist();
    const Playlist& playlist() const;

    bool isPlaying() const;
    bool isShuffleMode() const;
    bool isInfiniteMode() const;

private slots:
    void updatePlayer();
    void updateProgress();
    void navigatePlaylist();
    void updatePlaybackSpeed();
    void updatePlaybackControl();
    void toggleShuffleButton(bool value);
    void toggleInfiniteButton(bool value);

public slots:
    void stop();
    void replay();
    void forward();
    void changePlaybackMode();
    void changePlaybackSpeed();
    void setShuffleMode(bool value);
    void setInfiniteMode(bool value);

signals:
    void shuffleModeChanged(bool value);
    void infiniteModeChanged(bool value);

private:
    Playlist container;
    std::unique_ptr<Ui::Player> ui;
    std::unique_ptr<QAudioOutput> output;
    std::unique_ptr<QMediaPlayer> player;
};

#endif // PLAYER_H
