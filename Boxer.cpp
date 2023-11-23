#include "Boxer.h"

#include "Sprites.h"

#include "Game.h"

#include "GameConfig.h"

#include "Rat.h"

#include "Scrooge.h"

using namespace DT;

Boxer::Boxer(QPointF pos): Enemy(pos, 25, 30) {
    _jumping = false;
    _activated = false;
    _punching = false;
    _flying = true;
    _sprite = Sprites::instance() -> getSprite("boxer");
    _y_gravity = 0;
    Sprites::instance() -> get("boxer-jump-0", & _texture_walk[0]);
    Sprites::instance() -> get("boxer-jump-1", & _texture_walk[1]);

    Sprites::instance() -> get("boxer-punch-0", & _texture_punch[0]);
    Sprites::instance() -> get("boxer-punch-1", & _texture_punch[1]);

    Sprites::instance() -> get("boxer-stand", & _texture_jump[0]);

}

void Boxer::groundPhysics()
{
    defaultPhysics();
    _x_vel_max = 0.1;

}

void Boxer::advance() {

    if(!_activated){
        _activated = true;
        if(Game::instance()->player()->x() <= x()){
            _x_dir = Direction::LEFT;
            _mirror_x_dir = Direction::RIGHT;
        }else{
            _x_dir = Direction::RIGHT;
            _mirror_x_dir = Direction::LEFT;

        }
        schedule("ground", 20, [this](){defaultPhysics();  _flying = false; _x_dir = Direction::NONE;});
    }else if(!_flying && !midair()){
        if(abs(Game::instance()->player()->x() - x()) >= 3*TILE && !_punching){
            jump(true);
        }
        if(abs(Game::instance()->player()->x() - x()) < 3*TILE && !_jumping){
            _punching = true;
            if(Game::instance()->player()->x() <= x()){
                move(Direction::LEFT);
                _mirror_x_dir = Direction::RIGHT;
            }else{
                move(Direction::RIGHT);
                _mirror_x_dir = Direction::LEFT;
            }
        }

    }
    Entity::advance();
}

bool Boxer::animate() {
    if(_punching){
            _animRect = & _texture_punch[(FRAME_COUNT / 9) % 2];

    }else if(_jumping){
         _animRect = & _texture_jump[0];
    }
    else{
            _animRect = & _texture_walk[(FRAME_COUNT / 9) % 2];}
    return 1;
}

bool Boxer::hit(Object * what, Direction fromDir) {

    return false;
}

void Boxer::jump(bool on) {

    if (on) {
        velAdd(Vec2Df(0, -2.5));
        _jumping = true;
    };
}

void Boxer::die() {
    Enemy::die();
}
