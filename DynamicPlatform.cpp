#include "DynamicPlatform.h"
#include "Sprites.h"
#include "Game.h"
#include <QPainter>

using namespace DT;

DynamicPlatform::DynamicPlatform(QPointF pos, double width, double height) : Entity(pos, width, height)
{
    _compenetrable = false;
}

void DynamicPlatform::advance()
{
    Entity::advance();

    for (auto obj : _attached)
    {
        // object "on" the platform -> object moves along with platform
        if (obj.second == Direction::UP)
            obj.first->moveBy(_vel);

        // object hits platform from the bottom -> object pos corrected along y
        else if (obj.second == Direction::DOWN)
            obj.first->moveBy(Vec2Df(0, _vel.y));

        // object hits platform from one side -> object pos corrected along x
        else
            obj.first->moveBy(Vec2Df(_vel.x, 0));
    }
    _attached.clear();
}

bool DynamicPlatform::hit(Object* what, Direction fromDir)
{
    Entity* dyn = what->to<Entity*>();
    if (!_compenetrable && dyn && dyn->compenetrable())
        _attached[dyn] = fromDir;

    return false;
}
