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
    bool _launchable;
    bool _breakable;
    QRect _texture_block[3];


    bool _what_type;
    // animation textures


public:

    enum class Type {BRICK, SPHERE, QUESTION, HIDDEN, CHEST};
    Block::Type _type;

    Block(
            QPointF pos,
            double width,
            double height,
            Block::Type _type = Block::Type::BRICK);
    virtual bool animate() override;
    virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; ; }
    virtual bool hit(Object* what, Direction fromDir) override;
                                                                // implemented abstract methods
    /*
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Block"; }

         // actions
         virtual void smash();
         virtual void disable();
         virtual void smashAttached();

          // utility methods to create a rectangle filled will wall blocks
          static void createWall(int x, int y, int w, int h);
          */
};
