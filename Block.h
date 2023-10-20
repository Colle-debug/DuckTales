#pragma once

#include "DynamicPlatform.h"
//#include "Spawnable.h"

namespace DT
{
class Block;
}

class DT::Block : public Entity
{


protected:

    QPointF _pos;

           //Spawnable::Type _spawnable;
    bool _bouncing;
    bool _disabled;
    bool _spawned;
    bool _launched;
    bool _breakable;
    bool  _collided;
    bool _brick_breakable;QRect _texture_block[3];
    QRect _texture_broken_block[2];


    bool _what_type;
    // animation textures


public:

    enum class Type {BRICK, SPHERE, QUESTION, HIDDEN, CHEST};
    Block::Type _type;

    Block(
            QPointF pos,
            double width,
            double height,
            Block::Type _type);
    virtual bool animate() override;
    //virtual bool midair() const override;
    virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; ; }
    virtual bool hit(Object* what, Direction fromDir) override;

    
};
