#include "include/components/player.h"
#include <QMediaDevices>
#include <QAudioOutput>
#include <QAudioDevice>
#include "ui_player.h"

Player::Player(QWidget *parent) : QWidget(parent)
{
    ui = new Ui::Player;
    ui->setupUi(this);

    player = std::make_unique<QMediaPlayer>();
    output = std::make_unique<QAudioOutput>();

    output->setDevice(QMediaDevices::defaultAudioOutput());
    player->setAudioOutput(output.get());
}

Player::~Player()
{
    delete ui;
}
