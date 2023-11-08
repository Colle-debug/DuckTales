#include "Rat.h"
#include "Sprites.h"
using namespace DT;


Rat::Rat(QPointF pos) : Enemy(pos, 39, 27)
{
    _sprite = Sprites::instance()->getSprite("rat");
    Sprites::instance()->get("rat-default", &_texture_walk[0]);

}

void Rat::advance()
{
    //Scrooge* player = Game::instance()->player();
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

bool Rat::animate()
{
    _animRect = &_texture_walk[0];
    return true;
}

bool Rat::hit(Object* what, Direction fromDir)
{

    if (Enemy::hit(what, fromDir))
        return true;

    return false;
}
