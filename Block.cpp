#include "Block.h"
#include "Scrooge.h"
using namespace DT;

Block::Block(QPointF pos, double width, double height) :
    StaticObject(pos, width, height)
{
    setZValue(1);
}

bool Block::hit(Object* what, Direction fromDir)
{
    _hit = true;
    return true;
}
