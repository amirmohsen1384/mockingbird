#include <QDir>
#include <QListView>
#include <QApplication>
#include <QRandomGenerator64>
#include "include/dialogs/songedit.h"
#include "include/windows/welcomewindow.h"
#include "include/dialogs/playlistedit.h"
#include "include/models/playlistmodel.h"
#include "include/models/artistmodel.h"
#include "include/models/songdelegate.h"
#include "include/dialogs/artistview.h"
#include "include/dialogs/artistedit.h"
#include "include/dialogs/playlistplayer.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto songs = QDir("C:/Users/Amir Mohsen/Downloads/Music").entryInfoList({"*.mp3"}, QDir::AllEntries | QDir::NoDotAndDotDot);
    Playlist playlist;
    for(const QFileInfo &i : songs)
    {
        Song target;
        target.setGenre(static_cast<Song::Genre>(QRandomGenerator::global()->bounded(0, 7)));
        target.setPublicationYear(QRandomGenerator::global()->bounded(1996, 2016));
        target.setAddress(i.absoluteFilePath());
        target.setName(i.baseName());
        playlist.append(target);
    }
    playlist.setName("Sample Name");

    PlaylistEdit editor;
    editor.exec();

    return 0;
}
