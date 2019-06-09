QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    Bishop.cpp \
    BoardController.cpp \
    BoardGameWnd.cpp \
    King.cpp \
    Knight.cpp \
    MainWnd.cpp \
    Messenger.cpp \
    Move.cpp \
    MoveMng.cpp \
    Pawn.cpp \
    Piece.cpp \
    PieceFactory.cpp \
    Queen.cpp \
    Rook.cpp \
    Tile.cpp \
    Player.cpp \
    Minimax.cpp

HEADERS += \
    Bishop.h \
    BoardController.h \
    BoardGameWnd.h \
    BoardUntils.h \
    Defines.h \
    King.h \
    Knight.h \
    MainWnd.h \
    Messenger.h \
    Move.h \
    MoveMng.h \
    Pawn.h \
    Piece.h \
    PieceFactory.h \
    Queen.h \
    Rook.h \
    Singleton.h \
    Tile.h \
    Player.h \
    Minimax.h

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
