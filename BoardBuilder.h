#ifndef BOARDBUILDER_H
#define BOARDBUILDER_H

#include <map>

class Piece;
typedef std::map<const int, Piece*> BoardConfig;

class BoardBuilder
{
public:
    explicit BoardBuilder();

private:

};

#endif // BOARDBUILDER_H
