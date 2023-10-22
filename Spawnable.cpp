#include "Spawnable.h"
#include "Sprites.h"
#include "StaticObject.h"
#include "Block.h"
#include "Scrooge.h"
#include "Game.h"

using namespace DT;

Spawnable::Spawnable(QPointF pos, double width, double height, Spawnable::Type type, bool canFall) : Entity(pos, width, height){
    _sprite = Sprites::instance()->getSprite("spawnable");
    _compenetrable = true;
    _type = type;
    _canFall = canFall;
    if(_canFall){
        _y_gravity = 0;
    }
    else{
        _y_gravity = 0.5;
    }
    if(_type == Type::ICE_CREAM){
        Sprites::instance()->get("ice-cream", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::CAKE){
        Sprites::instance()->get("cake", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::DIAMOND_YELLOW_SMALL){
        _value = 10000;
        Sprites::instance()->get("diamond-small-0", &_texture_spawnable[0]);
        Sprites::instance()->get("diamond-small-1", &_texture_spawnable[1]);

        //_animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::DIAMOND_YELLOW_BIG){
        _value = 10000;
        Sprites::instance()->get("diamond-big-0", &_texture_spawnable[0]);
        Sprites::instance()->get("diamond-big-1", &_texture_spawnable[1]);
        Sprites::instance()->get("diamond-big-2", &_texture_spawnable[2]);
        Sprites::instance()->get("diamond-big-3", &_texture_spawnable[3]);
        //_animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::DIAMOND_RED_BIG){
        _value = 50000;
        Sprites::instance()->get("diamond-big-4", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::STAR){
        _value = 140; // x debugging
        Sprites::instance()->get("star-0", &_texture_spawnable[0]);
        Sprites::instance()->get("star-1", &_texture_spawnable[1]);
    }
    else if(_type == Type::KEY){
        Sprites::instance()->get("key", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::TREASURE){
        _value = 1000000;
        Sprites::instance()->get("treasure", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
}

bool Spawnable::animate()
{
    if(_canFall == 0 || (_canFall == 1 && _canFallHit == 1)){
    if(_type == Type::DIAMOND_YELLOW_BIG){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 4];
        }
    else if(_type == Type::DIAMOND_YELLOW_SMALL){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 2];
        }
    else if(_type == Type::STAR){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 2];
        }
    else if(_type == Type::DIAMOND_RED_BIG){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 1];
    }}
    else{
        _animRect = &_texture_spawnable[Qt::transparent];
    }

    return 1;
}

/*oid Spawnable::spawn()
{
    _y_gravity = 0.2;
    _vel.y = -0.5;
    _collidable = false;
    //Sounds::instance()->play("powerup-appear");
    //schedule("spawn", 32, [this]() { live(); });
}*/

bool Spawnable::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = what->to<Scrooge*>();
    //DynamicObject* dyn_obj = what->to<DynamicObject*>();


    if(scrooge && !_canFallHit && _canFall){
        _collidable = false; // Metto a true per non consentire a Scrooge di prenderlo mentre l'oggeto è in caduta
        schedule("fall", 10, [this]{_collidable=true;});
        _canFallHit = true;
        _y_gravity = 0.5;
        return true;
    }

    if (scrooge && !taken)
    {
        scrooge->scoreAdd(this->_value);
        if(_type == Type::ICE_CREAM || _type == Type::CAKE){
            scrooge->hpAdd(1);
        }
        else if(_type == Type::STAR){
            scrooge->setInvincible(true);
            schedule("invincible", 800, [scrooge]() {scrooge->setInvincible(false); });
        }
        else if(_type == Type::KEY){
            scrooge->setKeyStatus(true);
        }
        std::cout <<"Score: " <<scrooge->score() << "\n";
        taken = true;
        setVisible(false);
        return true;
    }

    return false;
}


