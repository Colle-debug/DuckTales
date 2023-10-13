#include "Block.h"
#include "Sprites.h"
#include "Scrooge.h"
//#include "Sounds.h"
#include "Enemy.h"
//#include "Spawnable.h"
//#include "BrokenBrick.h"
#include "Game.h"

using namespace DT;

Block::Block(QPointF pos, double width, double height, Block::Type type) : DynamicPlatform(pos, width, height)
{
    _pos = pos;
    _type = type;
    //_spawnable = spawnable;
    _bouncing = false;
    _disabled = false;
    _spawned = false;

    // default texture
    /*
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
/*
bool Block::animate()
{
    if (_type == Type::QUESTION && !_disabled)
        setPixmap(_texture_question[(FRAME_COUNT / 12) % 5]);

    return true;
}

bool Block::hit(Object* what, Direction fromDir)
{
    DynamicPlatform::hit(what, fromDir);

    Scrooge* mario = what->to<Scrooge*>();
    if (mario && fromDir == Direction::DOWN)
    {
        mario->velClipY(0);
        mario->jump(false);

        if (!_bouncing)
        {
            _compenetrable = false;	// hidden block now becomes solid

            // smash
            if ((_type == Block::Type::BRICK || _type == Block::Type::WALL))
            {
                // do 1-frame bounce to capture objects walking on this
                //bounce();
                schedule("one-frame-bounce", 1, [this]() {smash(); });
            }
            // bounce / bump
            else
            {
                //Sounds::instance()->play("bump");
                if (!_disabled)
                    //bounce();
            }
        }
    }

    if (_bouncing)
        smashAttached();

    return true;
}

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
