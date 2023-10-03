#ifndef BLOCK_H
#define BLOCK_H
#include "Entity.h"
#include "StaticObject.h"

namespace DT
{
    class Block;
}

class DT::Block : public StaticObject{
public:
    Block(QPointF pos, double width, double height) : StaticObject(pos,width,height){}
    
    virtual bool hit(Object* what, Direction fromDir) override{ return true; }
    virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; }
};

#endif
