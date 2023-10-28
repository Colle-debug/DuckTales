#include "Gizmoduck.h"
#include "Sprites.h"
#include "Scrooge.h"
#include "GameConfig.h"
using namespace DT;

Gizmoduck::Gizmoduck(QPointF pos, double width, double height):Entity(pos, width, height)
{
    _firing = false;
    _activated = false;
    _sprite = Sprites::instance()->getSprite("gizmoduck");
    Sprites::instance()->get("gizmoduck-0", &_texture_gizmoduck[0]);
    Sprites::instance()->get("gizmoduck-1", &_texture_gizmoduck[1]);

}

bool Gizmoduck::animate()
{
    if(!_activated){
        _animRect = &_texture_gizmoduck[Qt::transparent];
    }
    else{
        _animRect = &_texture_gizmoduck[(FRAME_COUNT / 9) % 2];;
    }
    return 1;
}

bool Gizmoduck::hit(Object *what, Direction fromDir)
{
    if(!_activated){
    Scrooge* scrooge = dynamic_cast<Scrooge*>(what);
    if(scrooge && fromDir == Direction::LEFT){
        _activated = true;
        _x_dir = Direction::RIGHT;
        velAdd(Vec2Df(2, 0));
        //schedule("stop", 50, [this]{velAdd(Vec2Df(-vel().versX(), 0));});
        }
    }
    return 0;
}
