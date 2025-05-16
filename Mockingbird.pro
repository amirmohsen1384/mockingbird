QT += core
QT += gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/core/playlist.h \
    include/core/song.h \
    include/core/admin.h \
    include/core/general.h \
    include/core/person.h \
    include/components/player.h \
    include/models/genremodel.h \
    include/models/playlistgroupmodel.h \
    include/models/playlistmodel.h \
    include/models/songdelegate.h \
    include/windows/welcomewindow.h

SOURCES += \
    src/core/admin.cpp \
    src/core/general.cpp \
    src/core/person.cpp \
    src/components/player.cpp \
    src/core/song.cpp \
    main.cpp \
    src/models/genremodel.cpp \
    src/models/playlistgroupmodel.cpp \
    src/models/playlistmodel.cpp \
    src/models/songdelegate.cpp \
    src/windows/welcomewindow.cpp

FORMS += \
    ui/components/player.ui \
    ui/windows/welcomewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
