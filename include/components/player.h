#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    Q_DISABLE_COPY_MOVE(Player)
    explicit Player(QWidget *parent = nullptr);
    ~Player();
    
    QUrl source() const;
    bool isShuffleMode() const;
    bool isInfiniteMode() const;

private slots:
    void updateMetaData();
    void updateProgress();
    void updatePlayback();
    void updateShuffleButton();
    void updatePlaybackSpeed();
    void updateSeekingControl();
    void updateInfiniteButton();

public slots:
    void stop();
    void replay();
    void forward();
    void controlPlayback();
    void controlPlaybackSpeed();
    void setShuffleMode(bool value);
    void setInfiniteMode(bool value);
    void setSource(const QUrl &source);

signals:
    void sourceFinished();
    void shuffleModeChanged(bool value);
    void infiniteModeChanged(bool value);

private:
    Ui::Player *ui;
    std::unique_ptr<QAudioOutput> output;
    std::unique_ptr<QMediaPlayer> player;
};

#endif // PLAYER_H
