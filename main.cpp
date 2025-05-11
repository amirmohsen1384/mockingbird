#include <QApplication>
#include "include/components/player.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Player player;

    return app.exec();
}
