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
protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();
    
    QUrl source() const;

public slots:
    void updateLoop();
    void updateMetaData();
    void updateProgress();
    void updatePlayback();
    void updatePlaybackSpeed();
    void updateSeekingControl();
    void setSource(const QUrl &source);

public slots:
    void stop();
    void replay();
    void forward();
    void controlPlayback();
    void controlPlaybackSpeed();

private:
    Ui::Player *ui;
    std::unique_ptr<QAudioOutput> output;
    std::unique_ptr<QMediaPlayer> player;
};

#endif // PLAYER_H
