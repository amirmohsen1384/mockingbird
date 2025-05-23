#include <QDir>
#include <QListView>
#include <QApplication>
#include <QRandomGenerator64>
#include "include/dialogs/songedit.h"
#include "include/windows/welcomewindow.h"
#include "include/dialogs/playlistedit.h"
#include "include/models/playlistmodel.h"
#include "include/models/artistmodel.h"
#include "include/dialogs/playlistplayer.h"
#include "include/models/songdelegate.h"
#include "include/dialogs/artistview.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto songs = QDir("C:/Users/Amir Mohsen/Downloads/Music").entryInfoList({"*.mp3"}, QDir::AllEntries | QDir::NoDotAndDotDot);
    PlaylistModel playlist;
    for(const QFileInfo &i : songs)
    {
        Song target;
        target.setGenre(static_cast<Song::Genre>(QRandomGenerator::global()->bounded(0, 7)));
        target.setPublicationYear(QRandomGenerator::global()->bounded(1996, 2016));
        target.setAddress(i.absoluteFilePath());
        target.setName(i.baseName());
        playlist.appendSong(target);
    }
    playlist.setName("My favorite songs");

    ArtistModel model;
    model.appendPlaylist(playlist.playlist());
    model.setName("Marshall Bruce Mathers III (Eminem)");
    model.setBiography("Eminem, born Marshall Bruce Mathers III, is one of the most influential and best-selling artists in the history of hip-hop. Known for his rapid-fire lyrics, complex rhyme schemes, and emotionally raw content, he gained worldwide fame in the late 1990s and early 2000s and helped bring hip-hop to a broader audience.");
    model.setPhoto(QPixmap("C:/Users/Amir Mohsen/Downloads/Sample.jpg"));

    ArtistView view;
    view.setModel(&model);
    view.exec();

    return 0;
}
