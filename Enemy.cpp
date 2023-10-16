#include "Enemy.h"
#include "GameConfig.h"
#include "Scrooge.h"
#include "StaticObject.h"
#include "Block.h"

using namespace DT;

Enemy::Enemy(QPointF pos, double width, double height) : Entity(pos, width, height)
{
    _collider.adjust(3, 3, -3, -1);
    _angry = false;
    _dying = false;
    _mirror_x_dir = Direction::LEFT;
}

bool Enemy::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = what->to<Scrooge*>();
    if (scrooge) // Da aggiungere condizione su invincibilità, vedi stessa funzione in Enemy su BubbleBobble
    {
        scrooge->lifeDown();
        return true;
    }
    else if (what->to<StaticObject*>() &&  _dying) // && fromDir == Direction::DOWN
    {
        //setVisible(false);
        // spawn item
        return true;
    }

    return false;
}

bool Enemy::animate()
{
    if(_dying)
        _animRect = &_texture_walk[(FRAME_COUNT / 4) % 4];
    else
        _animRect = &_texture_walk[(FRAME_COUNT / 9) % 2];

    return 1;
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