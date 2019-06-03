QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    Board.cpp \
    BoardController.cpp \
    BoardGameWnd.cpp \
    MainWnd.cpp \
    Messenger.cpp \
    Move.cpp \
    MoveMng.cpp \
    Piece.cpp \
    Tile.cpp

HEADERS += \
    Board.h \
    BoardController.h \
    BoardGameWnd.h \
    BoardUntils.h \
    Defines.h \
    MainWnd.h \
    Messenger.h \
    Move.h \
    MoveMng.h \
    Piece.h \
    Singleton.h \
    Tile.h

DISTFILES += \
    Resources/exit.png \
    Resources/GUI_temporary.PNG \
    Resources/new.png \
    Resources/open.png \
    Resources/Bb.svg \
    Resources/Bw.svg \
    Resources/Kb.svg \
    Resources/Kw.svg \
    Resources/Pb.svg \
    Resources/Pw.svg \
    Resources/Qb.svg \
    Resources/Qw.svg \
    Resources/Rb.svg \
    Resources/Rw.svg \
    Resources/Zb.svg \
    Resources/Zw.svg
