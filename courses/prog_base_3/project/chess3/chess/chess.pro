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
    selectfiguredialog.cpp \
    chessboard_load.cpp \
    chessboard_reset.cpp \
    chessboard_undo.cpp \
    chessboard_mouse.cpp \
    ChessEngine.cpp \
    ChessEngine_AI.cpp \
    ChessEngine_board.cpp \
    ChessEngine_getMoves.cpp \
    ChessEngine_reload.cpp \
    ChessEngine_undo.cpp \
    ChessEngine_utility.cpp \
    chessboard_flip.cpp \
    aboutdialog.cpp \
    selectcolodialog.cpp \
    chessboardcalcthread.cpp \
    chessboard_move.cpp \
    ChessEngine_move.cpp \
    chessboard_movethread.cpp \
    infodialog.cpp

HEADERS  += mainwindow.h \
    qsfmlcanvas.h \
    chessboard.h \
    resources.h \
    selectfiguredialog.h \
    figures.h \
    ChessEngine.h \
    aboutdialog.h \
    selectcolordialog.h \
    chessboardcalcthread.h \
    chessboard_movethread.h \
    infodialog.h

LIBS += -LC:/Frameworks/SFML-2.3.2/lib/

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += c:/Frameworks/SFML-2.3.2/include/
DEPENDPATH += c:/Frameworks/SFML-2.3.2/include/

FORMS    += mainwindow.ui \
    selectfiguredialog.ui \
    endgamedialog.ui \
    aboutdialog.ui \
    selectcolordialog.ui

CONFIG += c++11

RESOURCES += \
    resources.qrc
