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
    explicit Player(QWidget *parent = nullptr);
    ~Player();

private:
    Ui::Player *ui;
    std::unique_ptr<QAudioOutput> output;
    std::unique_ptr<QMediaPlayer> player;
};

#endif // PLAYER_H
