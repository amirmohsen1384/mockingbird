QT += core
QT += gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/components/playlistplayer.h \
    include/components/player.h \
    include/core/song.h \
    include/models/playlist.h \
    include/models/genremodel.h \
    include/models/playlistmodel.h

SOURCES += \
    src/components/playlistplayer.cpp \
    src/components/player.cpp \
    src/models/playlist.cpp \
    src/core/song.cpp \
    main.cpp \
    src/models/genremodel.cpp \
    src/models/playlistmodel.cpp

FORMS += \
    ui/components/playlistplayer.ui \
    ui/components/player.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
