#include "Scrooge.h"
#include "Game.h"
#include "Block.h"
#include <QDebug>
#include "GameConfig.h"
#include <QPainter>
#include <QPixmap>
#include "Sprites.h"

using namespace DT;
Scrooge::Scrooge(QPointF pos) : Entity(pos, TILE, TILE)
{
    setZValue(4);

    _collider.adjust(3, 3, -3, -1);
    _swinging = false;
    _dying = false;
    _pogoing = false;
    _climbing = false;
    _invincible = false;
    _prev_x_dir = Direction::RIGHT;
    _mirror_x_dir = Direction::LEFT;


    _scripted = false;
    _jumping = false;
    _gliding = false;


    _texture_stand[0] = Sprites::instance()->get("scrooge-stand");
    this->setPixmap(_texture_stand[0]);

}

void Scrooge::advance()
{
    if (grounded())
        _y_vel_max = 3;
    else if (falling())
        _y_vel_max = 1;

    Entity::advance();
}
void Scrooge::jump(bool on)
{
    if (_scripted)
        return;

    if (on)
    {
        if (!midair() || _gliding)
        {
            if (std::abs(_vel.x) <= 2.3123)
            {
                velAdd(Vec2Df(0, -4));
                _y_gravity = 0.1150;
            }
            else
            {
                velAdd(Vec2Df(0, -5));
                _y_gravity = 0.0938;
            }

            _jumping = true;
            //Sounds::instance()->play(std::string("jump-") + (_big ? "big" : "small"));
        }
    }
    else
        _y_gravity = 0.4375;
}

void Scrooge::animate()
{
    // animation step is implemented with division (/step)
    // animation cycle is implemented with modular division (%cycle size)
/*
    if(_dying)
        _animRect = &_animDie[(FRAME_COUNT / 9) % 4];
    else if (midair())
    {
        if (_vel.y < 0)
            _animRect = &_animJump[(FRAME_COUNT / 17) % 2];
        else
            _animRect = &_animFall[(FRAME_COUNT / 17) % 2];
    }
    else
    {
        if (_vel.x == 0)
            _animRect = &_animStand[(FRAME_COUNT / 17) % 2];
        else
            _animRect = &_animWalk[(FRAME_COUNT / 9) % 4];
    }
*/
    if (_invincible && (FRAME_COUNT / 4) % 2)
        _animRect = 0;
}

bool Scrooge::hit(Object* what, Direction fromDir)
{
    return false;
}


