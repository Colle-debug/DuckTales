#include "StaticObject.h"
#include "Game.h"
#include "Gizmoduck.h"
#include "Spawnable.h"
#include "Scrooge.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

using namespace DT;
StaticObject::StaticObject(QPointF pos, double width, double height, StaticObject::Type type) : Object(pos, width, height){
    _type = type;
    _hit = false;
    if(_type == Type::ROPE || _type == Type::ACTIVATOR){
        _compenetrable = true;
    }
    else if(_type == Type::BUMPER){
        _compenetrable = true;
        _bumper = 1;
    }
    else if(_type == Type::GREEN_GATE){
        _sprite = Sprites::instance()->getSprite("greenGate");
        Sprites::instance()->get("green-gate", &_texture_green_gate[0]);
        _animRect = &_texture_green_gate[0];
    }


}

bool StaticObject::animate()
{
    if(_type == Type::GREEN_GATE && !_hit){
        _animRect = &_texture_green_gate[(FRAME_COUNT / 9) % 1];
    }
    else if(_type == Type::GREEN_GATE && _hit){
        _animRect = &_texture_green_gate[Qt::transparent];
    }
    else if(_type == Type::ACTIVATOR){
        _animRect = &_texture_green_gate[Qt::transparent];
    }
    return false;
}

bool StaticObject::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = dynamic_cast<Scrooge*>(what);
    Spawnable* spawnable = dynamic_cast<Spawnable*>(what);
    if(scrooge && scrooge->hasTheKey() && this->_type == Type::GATE){
        _compenetrable = true;
        _hit = true;
        return true;
    }

    if(scrooge && scrooge->hasTheRemote() && _type == Type::ACTIVATOR){
        for (auto item: Game::instance()->world() -> items()) {
          Gizmoduck * gizmo = dynamic_cast < Gizmoduck * > (item);
          if(gizmo){
              gizmo->activate();
              scrooge->setGizmoCinematicStatus(true);
          }
        }

    }
    if(spawnable && spawnable->_type == Spawnable::Type::PROJECTILE){

        _compenetrable = true;
        _hit = true;
        setVisible(false);
        new StaticObject(QPointF(120*TILE,65*TILE), 0, 7*TILE, StaticObject::Type::ROPE);
        return true;
    }



    return false;
}



