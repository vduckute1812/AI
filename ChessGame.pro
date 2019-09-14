QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app


HEADERS += \
    BoardUntils.h \
    Controller/BoardController.h \
    Controller/Move.h \
    Controller/MoveMgr.h \
    Defines.h \
    GUI/BoardGameWnd.h \
    GUI/DeadPieceWnd.h \
    GUI/HistoryWnd.h \
    GUI/MainWnd.h \
    GUI/MessageBoxWnd.h \
    GUI/PromoteWnd.h \
    GUI/Tile.h \
    Messenger.h \
    Minimax/BonusSystem.h \
    Minimax/KingSafetyAnalyzer.h \
    Minimax/Minimax.h \
    Minimax/MoveSorter.h \
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
    Player.h \
    Singleton.h

SOURCES += \
    Controller/BoardController.cpp \
    Controller/Move.cpp \
    Controller/MoveMgr.cpp \
    GUI/BoardGameWnd.cpp \
    GUI/DeadPieceWnd.cpp \
    GUI/HistoryWnd.cpp \
    GUI/MainWnd.cpp \
    GUI/MessageBoxWnd.cpp \
    GUI/PromoteWnd.cpp \
    GUI/Tile.cpp \
    Messenger.cpp \
    Minimax/KingSafetyAnalyzer.cpp \
    Minimax/Minimax.cpp \
    Minimax/MoveSorter.cpp \
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
    Player.cpp \
    main.cpp

DISTFILES += \
    Resources/dead.png \
    Resources/exit.png \
    Resources/GUI_temporary.PNG \
    Resources/history.png \
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

