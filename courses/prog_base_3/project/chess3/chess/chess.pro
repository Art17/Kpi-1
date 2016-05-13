#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T13:49:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qsfmlcanvas.cpp \
    chessboard.cpp \
    movethread.cpp \
    chessengine.cpp

HEADERS  += mainwindow.h \
    qsfmlcanvas.h \
    chessboard.h \
    resources.h \
    movethread.h \
    chessengine.h

LIBS += -LC:/Frameworks/SFML-2.3.2/lib/

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += c:/Frameworks/SFML-2.3.2/include/
DEPENDPATH += c:/Frameworks/SFML-2.3.2/include/

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc
