CC = g++
CFLAGS = -Wall -Wextra -Wshadow -Wformat-nonliteral -Wformat-security -Wtype-limits -o2

OBJECTS = main.o \
	Bishop.o\
	King.o\
	Board.o\
	Pawn.o\
	Queen.o\
	Knight.o\
	Player.o\
	BoardController.o\
	Tile.o\
	Rook.o\

