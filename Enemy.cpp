#include "Enemy.h"
#include "GameConfig.h"
#include "Scrooge.h"
#include "StaticObject.h"
#include "Block.h"
#include "Sounds.h"

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
    if (scrooge && fromDir != Direction::UP) // Da aggiungere condizione su invincibilità, vedi stessa funzione in Enemy su BubbleBobble
    {
       
       
        if(!scrooge->invincibile()){
            scrooge->lifeDown();
           
            return true;
             
        }
    }/*
    else if(scrooge && scrooge->pogoing() && fromDir == Direction::UP){
        die();

        scrooge->_y_acc_up;
        return true;
    }*/
    else if (what->to<StaticObject*>() &&  _dying) // && fromDir == Direction::DOWN
    {
        //setVisible(false);
        // spawn item
        // schedule respawn?
        return true;
    }

    return false;
}

bool Enemy::animate()
{
    if(_dying)
        _animRect = &_texture_walk[1];
    else
        _animRect = &_texture_walk[(FRAME_COUNT / 9) % 2];

    return 1;
}

void Enemy::die()
{
    if (_dying)
        return;
  Sounds::instance()->play("enemydie");
         _dying = true;

        _collidable=false;
        schedule("die", 45, [this]() {setVisible(false); });
        _x_dir = Direction::DOWN;
           _y_gravity = 0.15;

        //_vel.y = -2.0;

       _vel.x=0.3;



        setY(y()-17);
        _y_acc_up = 2;

        _y_vel_max = 3;
        //_y_vel_min = 0.01;

        _x_vel_max = 3;
        _x_vel_min = 0.01;
}
