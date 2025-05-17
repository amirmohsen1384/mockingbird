#include <QApplication>
#include "include/components/songedit.h"
#include "include/windows/welcomewindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SongEdit window;
    window.show();

    app.exec();

    return 0;
}
