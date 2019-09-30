QT += core gui widgets

CONFIG += c++11

TARGET = ChessGame

TEMPLATE = app

SOURCES += main.cpp \
    Application.cpp \
    GUI/MenuComponents/GamePlayMenu/BoardGameWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/DeadPieceWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/HistoryWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/MainWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/MessageBoxWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/PromoteWnd.cpp \
    GUI/MenuComponents/GamePlayMenu/Tile.cpp \
    GUI/MenuComponents/MainMenu/MainMenuWnd.cpp \
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
    GUI/MenuComponents/GamePlayMenu/BoardGameWnd.h \
    GUI/MenuComponents/GamePlayMenu/DeadPieceWnd.h \
    GUI/MenuComponents/GamePlayMenu/HistoryWnd.h \
    GUI/MenuComponents/GamePlayMenu/MainWnd.h \
    GUI/MenuComponents/GamePlayMenu/MessageBoxWnd.h \
    GUI/MenuComponents/GamePlayMenu/PromoteWnd.h \
    GUI/MenuComponents/GamePlayMenu/Tile.h \
    GUI/MenuComponents/MainMenu/MainMenuWnd.h \
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
