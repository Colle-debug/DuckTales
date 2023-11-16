#include "StaticObject.h"
#include "Game.h"
#include "Gizmoduck.h"
#include "Spawnable.h"
#include "Scrooge.h"
#include "Beakley.h"
#include <QPainter>
#include <QBrush>
#include <QPen>

using namespace DT;

StaticObject::StaticObject(QPointF pos, double width, double height, StaticObject::Type type) : Object(pos, width, height){
    _type = type;
    _hit = false;
    _activated = false;
    if(_type == Type::ROPE){
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

StaticObject::StaticObject(QPointF pos, double width, double height, StaticObject::Activator type) : Object(pos, width, height)
{
    _type = Type::ACTIVATOR;
    _hit = false;
    activator_type = type;
    _compenetrable = true;

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
    Beakley *beakley = dynamic_cast<Beakley*>(what);
    if(scrooge && scrooge->hasTheKey() && this->_type == Type::GATE){
        _compenetrable = true;
        _hit = true;
        return true;
    }

    if(scrooge && _type == Type::ACTIVATOR){
        _hit = true;
        if(activator_type == Activator::GIZMO){
            Game::instance()->gizmo();
        }
        else if(activator_type == Activator::BOSS){
            Game::instance()->bossFight();
            setVisible(false);
        }
        else if(activator_type == Activator::BEAKLEY && !_activated){
            _activated = true;
            schedule("wait", 30, [this](){Game::instance()->beakleyDrop(); setVisible(false);});
        }

        else  if( activator_type == Activator::CAMERA && !scrooge->pogoing())
    {
        if (fromDir==Direction::DOWN){
        Game::instance()->cameraChangeY(Direction::DOWN); // Chiamata alla funzione nella classe Game
    }
    if (fromDir==Direction::UP)
        Game::instance()->cameraChangeY(Direction::UP);
      }
        
    }
        // if( activator_type == Activator::CAMERA)
        // {
        //     if (fromDir==Direction::DOWN){
        //         Game::instance()->cameraChangeY(Direction::DOWN); // Chiamata alla funzione nella classe Game
        //     }
        //     if (fromDir==Direction::UP){
        //         Game::instance()->cameraChangeY(Direction::UP);
        //     }
        // }
      
    else if(scrooge && _type == Type::RAT_WALL && fromDir == Direction::RIGHT){
        //flashingScreen(); Schermata nera mentre lo teletrasporta
      scrooge->setRatPit(true);
        scrooge->setPos(75*TILE, y());
    }

    


    /*if(scrooge && scrooge->hasTheRemote() && _type == Type::ACTIVATOR){
        for (auto item: Game::instance()->world() -> items()) {
          Gizmoduck * gizmo = dynamic_cast < Gizmoduck * > (item);
          if(gizmo){
              gizmo->activate();
              scrooge->setGizmoCinematicStatus(true);
          }
        }

    }*/
    
    // non dovrebbe servire questo
    if(spawnable && spawnable->_type == Spawnable::Type::PROJECTILE){

        _compenetrable = true;
        _hit = true;
        setVisible(false);
        //new StaticObject(QPointF(120*TILE,65*TILE), 0, 7*TILE, StaticObject::Type::ROPE);
        return true;
    }



    return false;


}

