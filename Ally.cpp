#include "Ally.h"
#include "GameConfig.h"
#include "Sprites.h"
using namespace DT;

Ally::Ally(QPointF pos, double width, double height, Ally::Type _type):Entity(pos, width, height)
{
    if(_type == Ally::Type::GIZMODUCK){
        _sprite = Sprites::instance()->getSprite("gizmoduck");
        Sprites::instance()->get("gizmoduck-0", &_texture_ally[0]);
        Sprites::instance()->get("gizmoduck-1", &_texture_ally[1]);
        _y_gravity = 0.5;
        _x_dir = Direction::RIGHT;
        _mirror_x_dir = Direction::LEFT;

        schedule("stop", 50, [this](){_x_dir = Direction::NONE;});
    }
}


bool Ally::animate()
{
    if(_type == Ally::Type::GIZMODUCK){
        _animRect = &_texture_ally[(FRAME_COUNT / 9) % 2];
    }
    return 1;
}

bool Ally::hit(Object *what, Direction fromDir)
{
    return 0;
}





