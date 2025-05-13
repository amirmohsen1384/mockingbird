#include <QApplication>
#include "include/components/player.h"
#include "playlistplayer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    PlaylistPlayer player;
    player.show();

    return app.exec();
}
