#include "Block.h"
#include "Sprites.h"
#include "Scrooge.h"
//#include "Sounds.h"
#include "Enemy.h"
#include "Spawnable.h"
#include "Game.h"
#include "StaticObject.h"

using namespace DT;

Block::Block(QPointF pos, double width, double height, Block::Type type) : Entity(pos, 16, 16)
{
    _pos = pos;
    _type = type;
    _spawned = false; // serve per gesittre quando respawna
    _breakable = false;
    _launched = false;
    _collided = false;
    

    _compenetrable = false;
    _sprite = Sprites::instance()->getSprite("block");

    Sprites::instance()->get("block-0", &_texture_block[0]);
    Sprites::instance()->get("block-1", &_texture_block[1]);
    Sprites::instance()->get("block-2", &_texture_block[2]);
    Sprites::instance()->get("block-broken-0", &_texture_broken_block[0]);
    Sprites::instance()->get("block-broken-1", &_texture_broken_block[1]);

    setZValue(1);
    _y_gravity = 0;
}

bool Block::animate()
{
     
    if (_type == Type::BRICK)
        _animRect = &_texture_block[0];


    if (_type == Type::SPHERE)
    {
        _animRect = &_texture_block[1];
    }

    if ((_type == Type::SPHERE || _type== Type::BRICK) && _breakable == true)
    {
        _animRect = &_texture_broken_block[(FRAME_COUNT / 4) % 4];
    }

    if(_launched && _type==Type::BRICK)   
    {
        if(_vel.y<0)
        _animRect = &_texture_block[2];
       else if (_vel.y>0)
        _animRect = &_texture_broken_block[(FRAME_COUNT / 4) % 4];    


    }

    return true;
}

bool Block::hit(Object* what, Direction fromDir)
{
    Scrooge* scrooge = what->to<Scrooge*>();
    Enemy* enm = what->to<Enemy*>();
    StaticObject* sobj = what->to<StaticObject*>();
    Block* block = what->to<Block*>();

    if (scrooge && fromDir == Direction::UP && scrooge->pogoing())
    {
        _breakable = true; //utilizzo breakable per gestire le interazioni con pogoing
        schedule("disappear", 20, [this]() { setVisible(false); });
    }

    if (scrooge && scrooge->swinging())
    {
        if (_type == Type::SPHERE)
        {
        if (fromDir == Direction::LEFT)
        {
            _x_dir = Direction::RIGHT;
            _y_acc_up = 0;
            velAdd(Vec2Df(10, -10));
        }
         if (fromDir == Direction::RIGHT)
        {
            _x_dir = Direction::LEFT;
            _y_acc_up = 0;
            velAdd(Vec2Df(-10, -10));
        }
       
    }

    if ( _type == Type::BRICK)
    {
        if (fromDir == Direction::LEFT)
        {
            velAdd(Vec2Df(0.15, -3));
            _x_dir = Direction::RIGHT;
            _y_gravity = 0.13;
            _compenetrable = true;
           schedule("disappear", 40, [this]() { setVisible(false); });
        }
        if (fromDir == Direction::RIGHT)
        {
            velAdd(Vec2Df(-0.15, -3));
            _x_dir = Direction::LEFT;
            _y_gravity = 0.13;
            _compenetrable = true;
            schedule("disappear", 40, [this]() { setVisible(false); });
        }
        
       _launched=true; //launched  serve per gestire le animazioni di brick quando viene hittato da scrooge
    }
     
    }

    if (enm && midair())
    {
        enm->die();
    }

    if ( sobj && fromDir==Direction::UP )
    {
        
        _compenetrable = true;
        _breakable=true;
       schedule("disappear", 8, [this]() { setVisible(false); });
        

        
    }
 
   /* if (block)  // da implementare le collisioni tra due blocchi. se si toccano solamente quello lanciato da scrooge deve rompersi. se collidano, il blocco deve essere non compenetrable e deve rompersi subito, attivo _breakable=true

    {
       
    }*/

    return true;
}




