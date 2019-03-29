QT += gui core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ChessGame
TEMPLATE = app

HEADERS += \
    Tile.h \
    Piece.h \
    MoveMgr.h \
    Move.h \
    BoardUntils.h \
    BoardUI.h \
    BoardBuilder.h \
    Board.h \
    Bishop.h \
    Singleton.h \
    BoardController.h \
    Rook.h \
    Queen.h \
    Pawn.h \
    Knight.h \
    King.h

SOURCES += \
    Tile.cpp \
    Piece.cpp \
    MoveMgr.cpp \
    Move.cpp \
    main.cpp \
    BoardUI.cpp \
    Board.cpp \
    Bishop.cpp \
    BoardBuilder.cpp \
    BoardController.cpp \
    Rook.cpp \
    Queen.cpp \
    Pawn.cpp \
    Knight.cpp \
    King.cpp
