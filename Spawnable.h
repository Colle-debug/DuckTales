#pragma once

#include "Entity.h"

namespace DT
{
class Spawnable;
}

class DT::Spawnable : public Entity
{
public:

    enum class Type { NONE, DIAMOND_BIG, STAR , DIAMOND_SMALL , ICE_CREAM };

    Spawnable(QPointF pos, double width, double height, Spawnable::Type _type);

    // implemented abstract methods
    //virtual bool animate() override { return false; }
    //virtual bool hit(Object* what, Direction fromDir) override;
    //virtual std::string name() override = 0;

           // default spawn and live phases
    //virtual void spawn();
    //virtual void live() = 0;

           // factory method
    //static Spawnable* instance(Type t, QPointF pos);
};
