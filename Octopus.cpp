#include "Octopus.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "StaticObject.h"
#include "Scrooge.h"

using namespace DT;

Octopus::Octopus(QPointF pos, Direction _type)
    : Enemy(pos, 16, 24)
{
    this->_type = _type;
    _sprite = Sprites::instance()->getSprite("octopus");
    if(_type == Direction::UP || _type == Direction::DOWN){
        _y_acc_up = 0.1;
        _y_vel_max = 1;
    }
    else{
        move(Direction::RIGHT);
        _y_gravity = 0;
    }
    Sprites::instance()->get("octopus-0", &_texture_walk[0]);
    Sprites::instance()->get("octopus-1", &_texture_walk[1]);

    /*Sprites::instance()->getAnimation("zenchan", &_animWalk[0][0]);
    Sprites::instance()->getAnimation("zenchan_angry", &_animWalk[1][0]);
    Sprites::instance()->getAnimation("zenchan_ball", &_animBubble[0][0]);
    Sprites::instance()->getAnimation("zenchan_ball_late", &_animBubble[1][0]);
    Sprites::instance()->getAnimation("zenchan_die", &_animDie[0]);*/
}

void Octopus::advance()
{
    Scrooge* player = Game::instance()->player();
    /*srand(time(0) + _id);
    if (grounded() || _x_dir == Direction::NONE)
    {
        if(std::abs(player->x() - x()) < 10)	// align with player before jump
            move(Direction::NONE);
        else if (player->x() < x())				// chase player with 80% probability
            move(rand()%10 > 2 ? Direction::LEFT : Direction::RIGHT);
        else if (player->x() > x())				// chase player with 80% probability
            move(rand() % 10 > 2 ? Direction::RIGHT : Direction::LEFT);
    }*/

    Enemy::advance();
}

bool Octopus::hit(Object* what, Direction fromDir)
{
    if (Enemy::hit(what, fromDir))
        return true;


    if (what->to<StaticObject*>() && (fromDir == Direction::UP || fromDir == Direction::DOWN) && (_type == Direction::UP || _type == Direction::DOWN))
    {
        move(inverse(_y_dir));
        _y_gravity *= -1;
        return true;
    }
    else if(what->to<StaticObject*>() && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT) && (_type == Direction::RIGHT || _type == Direction::LEFT)){
        move(inverse(_x_dir));
        return true;
    }
    return false;
}