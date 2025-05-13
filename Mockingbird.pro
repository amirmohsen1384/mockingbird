QT += core
QT += gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS += \
    include/components/player.h \
    include/core/playlist.h \
    include/core/song.h

SOURCES += \
    main.cpp \
    src/components/player.cpp \
    src/core/playlist.cpp \
    src/core/song.cpp

FORMS += \
    ui/components/player.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
