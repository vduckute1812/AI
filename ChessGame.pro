QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    Bishop.cpp \
    BoardController.cpp \
    BoardGameWnd.cpp \
    Client.cpp \
    DeadPieceWnd.cpp \
    HistoryWnd.cpp \
    King.cpp \
    KingSafetyAnalyzer.cpp \
    Knight.cpp \
    MainWnd.cpp \
    Messenger.cpp \
    Move.cpp \
    MoveMgr.cpp \
    MoveSorter.cpp \
    NetWorkEntity.cpp \
    Pawn.cpp \
    Piece.cpp \
    PieceFactory.cpp \
    PromoteWnd.cpp \
    Queen.cpp \
    Rook.cpp \
    Server.cpp \
    Tile.cpp \
    Player.cpp \
    Minimax.cpp

HEADERS += \
    Bishop.h \
    BoardController.h \
    BoardGameWnd.h \
    BoardUntils.h \
    BonusSystem.h \
    Client.h \
    DeadPieceWnd.h \
    Defines.h \
    HistoryWnd.h \
    King.h \
    KingSafetyAnalyzer.h \
    Knight.h \
    MainWnd.h \
    Messenger.h \
    Move.h \
    MoveMgr.h \
    MoveSorter.h \
    NetWorkEntity.h \
    Pawn.h \
    Piece.h \
    PieceFactory.h \
    PromoteWnd.h \
    Queen.h \
    Rook.h \
    Server.h \
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
