#ifndef STATICOBJECT_H_
#define STATICOBJECT_H_

#include "Object.h"


namespace DT
{
    class StaticObject;
}

class DT::StaticObject : public Object
{
    protected:
    bool _hit;
    public:

    StaticObject(QPointF pos, double width, double height);
        // implemented abstract methods
        virtual void advance() override {}
        virtual void animate() override {}

        // nonimplemented abstract methods
        virtual bool hit(Object* what, Direction fromDir) override; /*{ return true; }*/
        virtual std::string name() override { return "Block[" + std::to_string(_id) + "]"; }
};

#endif
