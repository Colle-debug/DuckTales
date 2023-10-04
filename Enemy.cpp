#include "Enemy.h"
#include "GameConfig.h"
#include "Scrooge.h"

#include "Block.h"

using namespace DT;

Enemy::Enemy(QPointF pos) : Entity(pos, TILE, TILE)
{
    _collider.adjust(3, 3, -3, -1);
    _angry = false;
    _dying = false;
    _mirror_x_dir = Direction::RIGHT;
}

bool Enemy::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = what->to<Scrooge*>();
    if (scrooge) // Da aggiungere condizione su invincibilità, vedi stessa funzione in Enemy su BubbleBobble
    {
        scrooge->lifeDown();
        return true;
    }
    else if (what->to<Block*>() && fromDir == Direction::DOWN && _dying)
    {
        setVisible(false);
        // spawn item
        return true;
    }

    return false;
}

void Enemy::animate()
{
    if(_dying)
        _animRect = &_animDie[(FRAME_COUNT / 4) % 4];
    else
        _animRect = &_animWalk[_angry][(FRAME_COUNT / 9) % 2];
}

void Enemy::die()
{
    if (_dying)
        return;

    _x_vel_max = 1;

    if (rand() % 2)
        _x_dir = Direction::RIGHT;
    else
        _x_dir = Direction::LEFT;

    velAdd(Vec2Df(0, -_y_acc_up));

    //Sounds::instance()->playSound("enemy_die");
    _dying = true;
}
