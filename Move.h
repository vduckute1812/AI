#ifndef MOVE_H
#define MOVE_H

class Board;
class Move
{
public:
    Move();
    Board* Execute();
    Board* Undo();
    Board* Redo();
};

#endif // MOVE_H
