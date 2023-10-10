#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

namespace DT
{
    class Enemy;
}

class DT::Enemy : public Entity
{
    protected:

        // state flags
        bool _angry;
        bool _dying;

        QRect _texture_walk[2];

        // animations
        QRect _animWalk[2][2];
        QRect _animBubble[2][2];
        QRect _animDie[4];

    public:

        Enemy(QPointF pos, double width, double height);

        // getters
        QPixmap* sprite() { return _sprite; }
        QRect* animBubble(bool late) { return &_animBubble[late][0]; }
        bool dying() { return _dying; }

        // implemented abstract methods
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual bool animate() override;

        // nonimplemented abstract methods
        virtual std::string name() override = 0;

        // actions
        virtual void die();
        //virtual void toAngry() { _angry = true; _x_vel_max = 2; }
};
#endif // ENEMY_H
