QT += core
QT += gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    artistedit.h \
    artistview.h \
    include/dialogs/playlistplayer.h \
    include/components/custom/arrangewidget.h \
    include/components/custom/filteredit.h \
    include/components/custom/findwidget.h \
    include/components/imageview.h \
    include/dialogs/songedit.h \
    include/core/artist.h \
    include/core/playlist.h \
    include/core/song.h \
    include/core/admin.h \
    include/core/general.h \
    include/core/person.h \
    include/components/player.h \
    include/models/artistmodel.h \
    include/models/genremodel.h \
    include/models/playlistmodel.h \
    include/models/proxyplaylistmodel.h \
    include/models/songdelegate.h \
    include/windows/welcomewindow.h \
    include/dialogs/playlistedit.h

SOURCES += \
    artistedit.cpp \
    artistview.cpp \
    src/dialogs/playlistedit.cpp \
    src/dialogs/playlistplayer.cpp \
    src/components/custom/arrangewidget.cpp \
    src/components/custom/filteredit.cpp \
    src/components/custom/findwidget.cpp \
    src/components/imageview.cpp \
    src/dialogs/songedit.cpp \
    src/core/admin.cpp \
    src/core/artist.cpp \
    src/core/general.cpp \
    src/core/person.cpp \
    src/components/player.cpp \
    src/core/playlist.cpp \
    src/core/song.cpp \
    main.cpp \
    src/models/artistmodel.cpp \
    src/models/genremodel.cpp \
    src/models/playlistmodel.cpp \
    src/models/proxyplaylistmodel.cpp \
    src/models/songdelegate.cpp \
    src/windows/welcomewindow.cpp

FORMS += \
    artistedit.ui \
    artistview.ui \
    ui/dialogs/playlistedit.ui \
    ui/dialogs/playlistplayer.ui \
    ui/components/custom/arrangewidget.ui \
    ui/components/custom/filteredit.ui \
    ui/components/custom/findwidget.ui \
    ui/components/player.ui \
    ui/dialogs/songedit.ui \
    ui/windows/welcomewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
