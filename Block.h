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
    bool _brick_breakable;
    bool _invisible;
    QRect _texture_block[3];
    QRect _texture_broken_block[2];
    QRect _texture_battery[1];
    QRect _texture_chest_big[1];
    QRect _texture_chest_small[1];


    //bool _what_type;
    // animation textures


public:

    enum class Type {BRICK, SPHERE, QUESTION, HIDDEN, CHEST_BIG, CHEST_SMALL, BATTERY};
    Block::Type _type;

    Block(
            QPointF pos,
            double width,
            double height,
            Block::Type _type,
            bool invisible=false);
    virtual bool animate() override;
    
    //virtual bool midair() const override;
    virtual std::string name() override { return "Block" ; }
    virtual bool hit(Object* what, Direction fromDir) override;

    
};
