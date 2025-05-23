#include <QDir>
#include <QApplication>
#include "include/dialogs/songedit.h"
#include "include/windows/welcomewindow.h"
#include "include/dialogs/playlistedit.h"
#include "include/models/playlistmodel.h"
#include "include/dialogs/playlistview.h"
#include <QRandomGenerator64>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto songs = QDir("C:/Users/Amir Mohsen/Downloads/Music").entryInfoList({"*.mp3"}, QDir::AllEntries | QDir::NoDotAndDotDot);
    std::shared_ptr<PlaylistModel> model = std::make_shared<PlaylistModel>();
    for(const QFileInfo &i : songs)
    {
        Song target;
        target.setGenre(static_cast<Song::Genre>(QRandomGenerator::global()->bounded(0, 7)));
        target.setPublicationYear(QRandomGenerator::global()->bounded(1996, 2016));
        target.setAddress(i.absoluteFilePath());
        target.setName(i.baseName());
        model->appendSong(target);
    }
    model->setName("Eminem Music");

    std::shared_ptr<ProxyPlaylistModel> proxy = std::make_shared<ProxyPlaylistModel>();
    proxy->setSourceModel(model.get());

    PlaylistView editor;
    editor.setModel(proxy);
    editor.show();

    return app.exec();
}
