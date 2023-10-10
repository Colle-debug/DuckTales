#include "Scrooge.h"
#include "Game.h"
#include "Block.h"
#include <QDebug>
#include "GameConfig.h"
#include <QPainter>
#include <QPixmap>
#include "Sprites.h"

using namespace DT;
Scrooge::Scrooge(QPointF pos) : Entity(pos, 26, 27)
{
    //setZValue(1);

    //_collider.adjust(3, 3, -3, -1);
    _swinging = false;
    _dying = false;
    _dead = false;
    _pogoing = false;
    _climbing = false;
    _invincible = false;
    _prev_x_dir = Direction::RIGHT;
    _mirror_x_dir = Direction::LEFT;
    _hp = 322;
    _recentlyHit = 0;

    _scripted = false;
    _jumping = false;
    _gliding = false;

    _sprite= Sprites::instance()->getSprite("scrooge");
    Sprites::instance()->get("scrooge-stand", &_texture_stand[0]);
    Sprites::instance()->get("scrooge-walk-0", &_texture_walk[0]);
    Sprites::instance()->get("scrooge-walk-1", &_texture_walk[1]);
    Sprites::instance()->get("scrooge-walk-2", &_texture_walk[2]);
    Sprites::instance()->get("scrooge-jump-fall", &_texture_jump[0]);
    Sprites::instance()->get("scrooge-bounce-0", &_texture_bounce[0]);
    Sprites::instance()->get("scrooge-bounce-1", &_texture_bounce[1]);
    Sprites::instance()->get("scrooge-crouch-0", &_texture_crouch[0]);
    Sprites::instance()->get("scrooge-crouch-1", &_texture_crouch[1]);
    Sprites::instance()->get("scrooge-stuck", &_texture_stuck[0]);
    Sprites::instance()->get("scrooge-climb-0", &_texture_climb[0]);
    Sprites::instance()->get("scrooge-climb-1", &_texture_climb[1]);
    Sprites::instance()->get("scrooge-preputt-0", &_texture_preputt[0]);
    Sprites::instance()->get("scrooge-preputt-1", &_texture_preputt[1]);
    Sprites::instance()->get("scrooge-putt-0", &_texture_putt[0]);
    Sprites::instance()->get("scrooge-putt-1", &_texture_putt[1]);
    Sprites::instance()->get("scrooge-putt-success-0", &_texture_puttsuccess[0]);
    Sprites::instance()->get("scrooge-putt-success-1", &_texture_puttsuccess[1]);
    Sprites::instance()->get("scrooge-putt-fail-0", &_texture_puttfail[0]);
    Sprites::instance()->get("scrooge-putt-fail-1", &_texture_puttfail[1]);
   // this->setPixmap(_texture_stand[0]);

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
                _y_gravity = 0.078;
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

bool Scrooge::animate()
{ 
    if (midair())
	{
		if (_vel.y < 0)
			_animRect = &_texture_jump[0];
		else
			_animRect = &_texture_jump[0];
	}
	else
	{ 
		if (_vel.x == 0)
			_animRect = &_texture_stand[0];
		else
			_animRect = &_texture_walk[(FRAME_COUNT / 9) % 4]; 
        }
        return 1;
}

bool Scrooge::hit(Object* what, Direction fromDir)
{
    return false;
}


void Scrooge::die()
{
    if (_dying)
        return;

    _dying = true;
    _collidable = false;
    _vel.x = 0;
    _x_dir = Direction::NONE;
    _vel.y = -3;
    schedule("die", 100, [this]() {_dying = false; _dead = true; } );
}


void Scrooge::lifeDown()
{
    if (_recentlyHit)
        return;

    if (_hp > 1)
    {
        _hp--;
        recentlyHit(true);
    }
    else
        die();
}

void Scrooge::recentlyHit(bool on)
{
    _recentlyHit = on;

    if(on)
        schedule("flash", 10, [this](){_recentlyHit = false; } );
}
