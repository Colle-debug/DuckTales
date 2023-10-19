#pragma once

#include "Entity.h"

namespace DT
{
class Spawnable;
}

class DT::Spawnable : public Entity
{
protected:
    double _value;
    bool taken = 0;
    QRect _texture_spawnable[5];
public:

    enum class Type { NONE, DIAMOND_BIG, STAR , DIAMOND_SMALL , ICE_CREAM };
    Spawnable::Type _type;

    double value(){return _value;}
    Spawnable(QPointF pos, double width, double height, Spawnable::Type _type);

    // implemented abstract methods
    virtual bool animate() override;
    virtual bool hit(Object* what, Direction fromDir) override;
    virtual std::string name() override { return "Spawnable"; }


           // default spawn and live phases
    virtual void spawn();


};
