#include <QDir>
#include <QApplication>
#include "include/dialogs/songedit.h"
#include "include/windows/welcomewindow.h"
#include "playlistedit.h"
#include "include/models/playlistmodel.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    auto songs = QDir("C:/Users/Amir Mohsen/Downloads/Music").entryInfoList({"*.mp3"}, QDir::AllEntries | QDir::NoDotAndDotDot);
    std::shared_ptr<PlaylistModel> model = std::make_shared<PlaylistModel>();
    for(const QFileInfo &i : songs)
    {
        Song target;
        target.setAddress(i.absoluteFilePath());
        target.setName(i.baseName());
        model->appendSong(target);
    }

    PlaylistEdit editor;
    editor.setModel(model);
    editor.show();

    return app.exec();
}
