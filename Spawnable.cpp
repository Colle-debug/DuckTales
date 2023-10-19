#include "Spawnable.h"
#include "Sprites.h"
#include "StaticObject.h"
#include "Block.h"
#include "Scrooge.h"
#include "Game.h"

using namespace DT;

Spawnable::Spawnable(QPointF pos, double width, double height, Spawnable::Type type) : Entity(pos, TILE, TILE){
    _sprite = Sprites::instance()->getSprite("spawnable");
    _compenetrable = true;
    _collidable = true;
    _type = type;
    if(_type == Type::ICE_CREAM){
        _value = 150;
        Sprites::instance()->get("ice-cream", &_texture_spawnable[0]);
        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::DIAMOND_BIG){

        _value = 300;
        Sprites::instance()->get("diamond-big-0", &_texture_spawnable[0]);
        Sprites::instance()->get("diamond-big-1", &_texture_spawnable[1]);
        Sprites::instance()->get("diamond-big-2", &_texture_spawnable[2]);
        Sprites::instance()->get("diamond-big-3", &_texture_spawnable[3]);
        Sprites::instance()->get("diamond-big-4", &_texture_spawnable[4]);

        _animRect = &_texture_spawnable[0];
    }
    else if(_type == Type::STAR){
        _value = 450;
        Sprites::instance()->get("star-0", &_texture_spawnable[0]);
        Sprites::instance()->get("star-1", &_texture_spawnable[1]);
    }


}

bool Spawnable::animate()
{
    if(_type == Type::DIAMOND_BIG){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 5];
    }
    else if(_type == Type::STAR){
        _animRect = &_texture_spawnable[(FRAME_COUNT / 9) % 2];
    }
    return 1;

}

void Spawnable::spawn()
{
    _y_gravity = 0;
    _vel.y = -0.5;
    _collidable = false;
    //Sounds::instance()->play("powerup-appear");
    //schedule("spawn", 32, [this]() { live(); });
}

bool Spawnable::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = what->to<Scrooge*>();
    //DynamicObject* dyn_obj = what->to<DynamicObject*>();
    if (scrooge && !taken)
    {
        scrooge->scoreAdd(this->_value);
        std::cout <<"Score: " <<scrooge->score() << "\n";
        taken = true;
        setVisible(false);
        return true;
    }

    return false;
}


