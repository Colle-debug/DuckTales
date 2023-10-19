#include "BBoy.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "StaticObject.h"
#include "Scrooge.h"

using namespace DT;

BBoy::BBoy(QPointF pos)
    : Enemy(pos, 25, 32)
{
    _jumping = false;
    _sprite = Sprites::instance()->getSprite("beagleBoy");
    _x_dir = Direction::RIGHT;

    Sprites::instance()->get("beagleBoy-0", &_texture_walk[0]);
    Sprites::instance()->get("beagleBoy-1", &_texture_walk[1]);
    Sprites::instance()->get("beagleBoy-1", &_texture_walk[2]);
}

void BBoy::advance()
{
    _prev_x_val = x();
    Scrooge* player = Game::instance()->player();
    if(abs(player->x() - x()) > 8*TILE && player->y() >= 73 *TILE){
        setVisible(false);
        Game::instance()->setBeagleStatus(false);
    }

    Enemy::advance();
}

bool BBoy::animate()
{
    _animRect = &_texture_walk[(FRAME_COUNT / 9) % 3];
    return 1;
}

bool BBoy::hit(Object* what, Direction fromDir)
{

    if (Enemy::hit(what, fromDir))
        return true;

    if (what->to<StaticObject*>() && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT))
    {
        fromDirBackup = fromDir;
        jump();
        schedule("check", 4, [this]() {checkPos();});
        return true;
    }

    return false;
}

void BBoy::jump(bool on)
{

    if (on)
    {
        if (!midair())
        {
            if (std::abs(_vel.x) <= 2)
            {
                velAdd(Vec2Df(0, -3));
                _y_gravity = 0.078;
            }
            else
            {
                velAdd(Vec2Df(0, -5));
                _y_gravity = 0.1;
            }

            _jumping = true;
            //Sounds::instance()->play(std::string("jump-") + (_big ? "big" : "small"));
        }
    }
    else
        _y_gravity = 0.8;
}

void BBoy::die()
{
    Game::instance()->setBeagleStatus(false);
    Enemy::die();
}

void BBoy::checkPos(){
    if(x() == _prev_x_val){
        _x_dir = fromDirBackup;
    }
}
