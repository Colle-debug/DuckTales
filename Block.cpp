#include "Block.h"
#include "Sprites.h"
#include "Scrooge.h"
//#include "Sounds.h"
#include "Enemy.h"
#include "Spawnable.h"
#include "Game.h"


using namespace DT;

Block::Block(QPointF pos, double width, double height,Block::Type type) : Entity(pos,16,16)
{
    _pos = pos;
    _type = type;
    //_spawnable = spawnable;
    _bouncing = false;
    _disabled = false;
    _spawned = false;
    _breakable = false;
    _launchable = false;

    _compenetrable=false;
    _sprite= Sprites::instance()->getSprite("block");

    Sprites::instance()->get("block-0",&_texture_block[0]);
    Sprites::instance()->get("block-1",&_texture_block[1]);
    Sprites::instance()->get("block-2",&_texture_block[2]);



    // default texture
    /*_sprite= Sprites::instance()->getSprite("scrooge");
    Sprites::instance()->get("scrooge-stand", &_texture_stand[0]);
    _texture_question[0] = Sprites::instance()->get("question-0");
    _texture_question[1] = Sprites::instance()->get("question-1");
    _texture_question[2] = Sprites::instance()->get("question-2");
    _texture_question[3] = Sprites::instance()->get("question-1");
    _texture_question[4] = Sprites::instance()->get("question-0");
    */
    /*
    if (_type == Type::QUESTION)
        setPixmap(_texture_question[0]);
    else if (_type == Type::BRICK)
        setPixmap(Sprites::instance()->get("brick"));
    else if (_type == Type::WALL)
        setPixmap(Sprites::instance()->get("wall"));
    else // hidden
    {
        _compenetrable = true;
        setPixmap(Sprites::instance()->get("invisible"));
    }*/
    setZValue(1);

           // default physics
    _y_gravity = 0;

}

bool Block::animate()
{
    if (_type == Type::BRICK)
        _animRect = &_texture_block[0];
    return true;
}

bool Block::hit(Object* what, Direction fromDir)
{
    Scrooge* mario = what->to<Scrooge*>();
    if (mario && fromDir == Direction::UP && _type == Type::BRICK && mario->pogoing())
      {
        setVisible(false);
        _compenetrable = true;

        if (chanceCalculator(0.25)) { // 25% di probabilità di spawnare un oggetto
            new Spawnable(this->_pos, TILE, TILE, Spawnable::Type::STAR);
        }

        /*_x_dir = Direction::RIGHT;
        _y_acc_up = 0;
        velAdd(Vec2Df(10, -10));*/

          return true;
      }
    /*           // smash
               if ((_type == Block::Type::BRICK)
               {

                 // do 1-frame bounce to capture objects walking on this
                 //bounce();
                // schedule("one-frame-bounce", 1, [this]() {smash(); });
             }
             // bounce / bump
             else
             {
                 //Sounds::instance()->play("bump");
                 if (!_disabled)
                     //bounce();
             }
         }*/

    return false;

}




/*

void Block::bounce()
{
 if (_bouncing)
     return;
 _bouncing = true;

 // single spawnable cause the block to disable immediately
 if (_spawnable != Spawnable::Type::NONE && _spawnable != Spawnable::Type::MULTICOIN)
     disable();
 // multicoin becomes single coin after expiration
 if (!_spawned && _spawnable == Spawnable::Type::MULTICOIN)
     schedule("multicoin", 300, [this]() {_spawnable = Spawnable::Type::COIN; });
 // coins spawn immediately
 if (_spawnable == Spawnable::Type::COIN || _spawnable == Spawnable::Type::MULTICOIN)
 {
     Spawnable::instance(_spawnable, pos());
     _spawned = true;
 }

 // bounce physics with delayed spawn
 _y_gravity = 0.2;
 _vel.y = -2;
 schedule("spawn", 19, [this]() {
     _y_gravity = 0;
     _vel.y = 0;
     _bouncing = false;
     setPos(_pos);
     if (_spawnable != Spawnable::Type::NONE &&
         _spawnable != Spawnable::Type::COIN &&
         _spawnable != Spawnable::Type::MULTICOIN)
     {
         Spawnable::instance(_spawnable, pos());
         _spawned = true;
     }
 });
}

void Block::smash()
{
 setVisible(false);
 Sounds::instance()->play("smash");
 new BrokenBrick(_pos + QPointF(8, 0), -3, 2);
 new BrokenBrick(_pos + QPointF(0, 0), -3, -2);
 new BrokenBrick(_pos + QPointF(8, 8), -1, 2);
 new BrokenBrick(_pos + QPointF(0, 8), -1, -2);
 Game::instance()->hud()->addScore(50);
}
void Block::disable()
{
    _disabled = true;
    setPixmap(Sprites::instance()->get("block-disabled"));
}

void Block::createWall(int x, int y, int w, int h)
{
    for (int i = y; i < y + h; i++)
        for (int j = x; j < x + w; j++)
            new Block(QPoint(j * TILE, i * TILE), Block::Type::WALL);
}

void Block::smashAttached()
{
    for (auto obj : _attached)
    {
        Enemy* enemy = obj.first->to<Enemy*>();
        Spawnable* spawnable = obj.first->to<Spawnable*>();
        if (enemy)
            enemy->smash(this);
        else if (spawnable)
        {
            spawnable->jump();
            spawnable->move(spawnable->isRightTo(this) ? Direction::RIGHT : Direction::LEFT);
        }
    }
    _attached.clear();
}
*/
