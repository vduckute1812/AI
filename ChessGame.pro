QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    GUI/BoardGameWnd.cpp \
    GUI/DeadPieceWnd.cpp \
    GUI/HistoryWnd.cpp \
    GUI/MainWnd.cpp \
    GUI/MessageBoxWnd.cpp \
    GUI/PromoteWnd.cpp \
    GUI/Tile.cpp \
    Controller/BoardController.cpp \
    Controller/Move.cpp \
    Controller/MoveMgr.cpp \
    Network/Client.cpp \
    Network/NetWorkEntity.cpp \
    Network/Server.cpp \
    Piece/Bishop.cpp \
    Piece/King.cpp \
    Piece/Knight.cpp \
    Piece/Pawn.cpp \
    Piece/Piece.cpp \
    Piece/PieceFactory.cpp \
    Piece/Queen.cpp \
    Piece/Rook.cpp \
    Messenger.cpp \
    Player.cpp

HEADERS += \
    GUI/BoardGameWnd.h \
    GUI/DeadPieceWnd.h \
    GUI/HistoryWnd.h \
    GUI/MainWnd.h \
    GUI/MessageBoxWnd.h \
    GUI/PromoteWnd.h \
    GUI/Tile.h \
    Controller/BoardController.h \
    Controller/Move.h \
    Controller/MoveMgr.h \
    Network/Client.h \
    Network/NetWorkEntity.h \
    Network/Server.h \
    Piece/Bishop.h \
    Piece/King.h \
    Piece/Knight.h \
    Piece/Pawn.h \
    Piece/Piece.h \
    Piece/PieceFactory.h \
    Piece/Queen.h \
    Piece/Rook.h \
    BoardUntils.h \
    Defines.h \
    Messenger.h \
    Player.h \
    Singleton.h

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
