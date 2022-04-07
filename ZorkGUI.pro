QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Character.cpp \
    Command.cpp \
    Room.cpp \
    ZorkUL.cpp \
    enemy.cpp \
    gobelin.cpp \
    healthpotion.cpp \
    inventorywidget.cpp \
    item.cpp \
    key.cpp \
    main.cpp \
    mainwindow.cpp \
    weapon.cpp \
    wordle.cpp

HEADERS += \
    Character.h \
    Command.h \
    Room.h \
    ZorkUL.h \
    enemy.h \
    gobelin.h \
    healthpotion.h \
    inventorywidget.h \
    item.h \
    key.h \
    mainwindow.h \
    weapon.h \
    wordle.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

DISTFILES += \
    words.txt
