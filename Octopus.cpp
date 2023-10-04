#include "Octopus.h"
#include "Sprites.h"
#include "Game.h"
#include "GameConfig.h"
#include "Block.h"
#include "Scrooge.h"

using namespace DT;

Octopus::Octopus(QPointF pos)
    : Enemy(pos)
{
    _sprite = Sprites::instance()->getSprite("octopus");
    move(Direction::RIGHT);

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

    if (what->to<Block*>() && (fromDir == Direction::RIGHT || fromDir == Direction::LEFT))
    {
        move(inverse(_x_dir));
        return true;
    }

    return false;
}
