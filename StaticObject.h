#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "Object.h"


namespace DT
{
    class StaticObject;

}

class DT::StaticObject : public Object
{
    public:
    enum class Type{TERRAIN, ROPE, SPIKE, GATE, BUMPER, DEATHLINE};
    protected:
        bool _hit;
    public:

        StaticObject(QPointF pos, double width, double height, StaticObject::Type type = StaticObject::Type::TERRAIN);
        // implemented abstract methods
        StaticObject::Type _type;
        virtual void advance() override {}
        virtual bool animate() override;
        virtual bool hit(Object* what, Direction fromDir) override;
        virtual std::string name() override { return "StaticObject"; }
};



#endif
