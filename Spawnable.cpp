#include "Spawnable.h"
#include "Sprites.h"

#include "Game.h"

using namespace DT;

Spawnable::Spawnable(QPointF pos, double width, double height, Spawnable::Type _type) : Entity(pos, width, height){
    setZValue(0);

}
/*
void Spawnable::spawn()
{
    _y_gravity = 0;
    _vel.y = -0.5;
    _collidable = false;
    Sounds::instance()->play("powerup-appear");
    schedule("spawn", 32, [this]() { live(); });
}

bool Spawnable::hit(Object* what, Direction fromDir)
{
    StaticObject* stc_obj = what->to<StaticObject*>();
    DynamicObject* dyn_obj = what->to<DynamicObject*>();
    if ( (stc_obj || (dyn_obj && !dyn_obj->compenetrable())) &&
        (fromDir == Direction::LEFT || fromDir == Direction::RIGHT))
    {
        move(inverse(_x_dir));
        return true;
    }

    return false;
}

// factory method
Spawnable* Spawnable::instance(Type t, QPointF pos)
{
    if (t == Spawnable::Type::POWERUP)
    {
        if (Game::instance()->mario()->small())
            return new Mushroom(pos);
        else
            return new Flower(pos);
    }
    else if (t == Spawnable::Type::LIFE)
        return new Mushroom(pos, true);
    else if (t == Spawnable::Type::STAR)
        return new Star(pos);
    else if (t == Spawnable::Type::COIN || t == Spawnable::Type::MULTICOIN)
        return new CoinSpawnable(pos);
    else if (t == Spawnable::Type::VINE)
            return new Vine(pos);
    else
        return nullptr;
}*/
