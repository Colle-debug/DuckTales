#include "Launchpad.h"
#include "GameConfig.h"
#include "Sprites.h"
#include "Game.h"
#include "Scrooge.h"
using namespace DT;

Launchpad::Launchpad(QPointF pos, double width, double height):Entity(pos, width, height)
{
    _sprite = Sprites::instance()->getSprite("launchpad");
    Sprites::instance()->get("launchpad-standing", &_texture_launchpad[0]);
    Sprites::instance()->get("launchpad-flying-0", &_texture_launchpad_flying[0]);
    Sprites::instance()->get("launchpad-flying-1", &_texture_launchpad_flying[1]);

    _animRect = &_texture_launchpad[0];
}


bool Launchpad::animate()
{
    if(_flying){
        _boundingRect = QRectF(0, 0, 53, 71);
        _collider = _boundingRect;
        _animRect = &_texture_launchpad_flying[(FRAME_COUNT / 9) % 2];
    }
    return 1;
}

bool Launchpad::hit(Object *what, Direction fromDir)
{
    Scrooge* scrooge = dynamic_cast<Scrooge*>(what);
    if(scrooge && !_flying){
        flyingAnimation();
    }
    return 0;
}

void Launchpad::flyingAnimation()
{
    _flying = true;
    setPos(40*TILE, 10*TILE);
    _y_gravity = 0;
    _x_dir == Direction::LEFT;
    velAdd(Vec2Df(0.5, 0));
}







