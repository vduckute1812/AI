QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    Application.cpp \
    GUI/MenuComponents/BoardGameWnd.cpp \
    GUI/MenuComponents/DeadPieceWnd.cpp \
    GUI/MenuComponents/HistoryWnd.cpp \
    GUI/MenuComponents/MainWnd.cpp \
    GUI/MenuComponents/MessageBoxWnd.cpp \
    GUI/MenuComponents/PromoteWnd.cpp \
    GUI/MenuComponents/Tile.cpp \
    GUI/MenuFactory.cpp \
    GUI/MenuManager.cpp \
    GUI/Menus/IMenu.cpp \
    GUI/Menus/LoginMenu.cpp \
    GUI/Menus/MainMenu.cpp \
    GUI/Menus/OptionMenu.cpp \
    GUI/Menus/PlayGameMenu.cpp \
    GUI/Menus/ScoreMenu.cpp \
    Controller/BoardController.cpp \
    Controller/Move.cpp \
    Controller/MoveMgr.cpp \
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
    Messenger.cpp \
    Player.cpp

HEADERS += \
    Application.h \
    GUI/MenuComponents/BoardGameWnd.h \
    GUI/MenuComponents/DeadPieceWnd.h \
    GUI/MenuComponents/HistoryWnd.h \
    GUI/MenuComponents/MainWnd.h \
    GUI/MenuComponents/MessageBoxWnd.h \
    GUI/MenuComponents/PromoteWnd.h \
    GUI/MenuComponents/Tile.h \
    GUI/MenuFactory.h \
    GUI/MenuManager.h \
    GUI/Menus/IMenu.h \
    GUI/Menus/LoginMenu.h \
    GUI/Menus/MainMenu.h \
    GUI/Menus/OptionMenu.h \
    GUI/Menus/PlayGameMenu.h \
    GUI/Menus/ScoreMenu.h \
    Controller/BoardController.h \
    Controller/Move.h \
    Controller/MoveMgr.h \
    Minimax/BonusSystem.h \
    Minimax/KingSafetyAnalyzer.h \
    Minimax/Minimax.h \
    Minimax/MoveSorter.h \
    MoveDefine.h \
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
