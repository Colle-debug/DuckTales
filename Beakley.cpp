#include "Beakley.h"
#include "Sprites.h"
#include "Scrooge.h"
#include "GameConfig.h"
#include "Spawnable.h"
using namespace DT;

Beakley::Beakley(QPointF pos, double width, double height):Entity(pos, width, height)
{
   
    _activated = false;
    _sprite = Sprites::instance()->getSprite("beakley");
    Sprites::instance()->get("beakley-0", &_texture_beakley[0]);
    Sprites::instance()->get("beakley-1", &_texture_beakley[1]);
    Sprites::instance()->get("beakley-1", &_texture_beakley[2]);

}

bool Beakley::animate() 
{
    
        _animRect = &_texture_beakley[(FRAME_COUNT / 10) % 2];
    
    return 1;
}

// bool Beakley::activate()
// {
//     //     _activated = true;
//     //     _x_dir = Direction::RIGHT;
//     //     schedule("stop", 50, [this]{_x_dir = Direction::NONE;});
//     //     schedule("fire", 80, [this]{firing();});
//     //     schedule("backoff", 120, [this]{_x_dir = Direction::LEFT;});
//     //     schedule("disappear", 200, [this]{setVisible(false);});

//     // return 0;
// }

// void Beakley::firing()
// {
//     // Spawnable* projectile = new Spawnable(QPointF(x() + TILE, y() + TILE), TILE/2, TILE/2, Spawnable::Type::PROJECTILE);
//     // projectile->_y_gravity = 0;
//     // projectile->_x_dir = Direction::RIGHT;
// }
