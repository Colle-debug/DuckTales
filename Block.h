#pragma once

#include "DynamicPlatform.h"
//#include "Spawnable.h"

namespace DT
{
    class Block;
}

class DT::Block : public DynamicPlatform
{
    public:

        enum class Type {BRICK, SPHERE, QUESTION, HIDDEN};

    protected:

        QPointF _pos;
        Block::Type _type;
        //Spawnable::Type _spawnable;
        bool _bouncing;
        bool _disabled;
        bool _spawned;

        // animation textures
        QPixmap _texture_question[5];

    public:

        Block(
            QPointF pos,
            double width,
            double height,
            Block::Type type = Block::Type::BRICK);

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
