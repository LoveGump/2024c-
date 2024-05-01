QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia

CONFIG += resources_big
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    brick.cpp \
    castle.cpp \
    game_help.cpp \
    game_pause.cpp \
    game_scene.cpp \
    main.cpp \
    mainwindow.cpp \
    mario.cpp \
    mushroom.cpp \
    my_pushbutton.cpp \
    pipe.cpp \
    unkown_surprise.cpp

HEADERS += \
    brick.h \
    castle.h \
    game_help.h \
    game_pause.h \
    game_scene.h \
    mainwindow.h \
    mario.h \
    mushroom.h \
    my_pushbutton.h \
    pipe.h \
    unkown_surprise.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
